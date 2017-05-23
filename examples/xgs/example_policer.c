/*********************************************************************
 *
 * (C) Copyright Broadcom Corporation 2013-2017
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 **********************************************************************
 *
 * \file         example_policer.c
 *
 * \brief        OpenNSL example application for policer or service meter
 *
 * \details       In this example, we will create a simple two rate, three color policer. 
 *                This policer will be attached to a Field Processor rule that counts 
 *                packets ingressing on a selected port with a specific VLAN Id. 
 *                Packets that exceed peak rate will be colored red.  A field processor 
 *                stat counter will be attached that counts "red" and "not red" bytes.
 *
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opennsl/error.h>
#include <opennsl/port.h>
#include <opennsl/vlan.h>
#include <opennsl/field.h>
#include <opennsl/policer.h>
#include <examples/util.h>

#define DEFAULT_UNIT 0
#define DEFAULT_VLAN 1


opennsl_error_t
example_create_policer(int unit, opennsl_field_group_t * group, opennsl_port_t port, opennsl_vlan_t vlan,
                       int index, int *statId)
{
    opennsl_field_stat_t stats[2] = {
        opennslFieldStatRedBytes, opennslFieldStatNotRedBytes
    };

    /*
     * Choose rates that don't overlap to simplify validation.  Make bit
     * rates even muliples of 8
     * */
    const int   base_rate = (index + 1) * 50;
    const int   cir = base_rate * 8;
    const int   cbs = (base_rate + 200) * 8;
    const int   pir = (base_rate + 400) * 8;
    const int   pbs = (base_rate + 600) * 8;

    opennsl_policer_t policer_id;
    opennsl_field_entry_t entry;
    opennsl_policer_config_t policer_config;

    if (*group < 0) {
        /* Only create group once, all entries share the same group */
        opennsl_field_qset_t qset;
        /* Create QSET. */
        OPENNSL_FIELD_QSET_INIT(qset);
        /* Specifiy Ingress Field Processor */
        OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyStageIngress);
        /* Match on outer VLAN ID and Ingress Port */
        OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyOuterVlanId);
        OPENNSL_FIELD_QSET_ADD(qset, opennslFieldQualifyInPort);

        OPENNSL_IF_ERROR_RETURN(opennsl_field_group_create
                            (unit, qset, OPENNSL_FIELD_GROUP_PRIO_ANY, group));
    }

    /* Create a field processor entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_create(unit, *group, &entry));

    /* Match on Ingress port and VLAN ID */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_qualify_InPort(unit, entry, port, 0xFF));
    OPENNSL_IF_ERROR_RETURN(opennsl_field_qualify_OuterVlanId(unit, entry, vlan, 0xFFF));

    /* Fill out policer configuration */
    opennsl_policer_config_t_init(&policer_config);
    policer_config.mode = opennslPolicerModeTrTcm;  /* Two rate, three color policer */
    policer_config.flags |= OPENNSL_POLICER_COLOR_BLIND;    /* Ignore previous color */
    policer_config.ckbits_sec = cir;    /* Committed Rate, below this rate, packets are green */
    policer_config.ckbits_burst = cbs;
    policer_config.pkbits_sec = pir;    /* Peak Rate, below rate is yellow, above rate is red */
    policer_config.pkbits_burst = pbs;

    /* Create the policer */
    OPENNSL_IF_ERROR_RETURN(opennsl_policer_create(unit, &policer_config, &policer_id));

    /* Attach policer to the entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_policer_attach(unit, entry, 0, policer_id));

    /* Add an FP rule to drop all red packets */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_action_add(unit, entry, opennslFieldActionRpDrop, 0, 0));

    /* Create a statistics entry to keep track of red/not-red traffic */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_stat_create(unit, *group, 2, stats, statId));
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_stat_attach(unit, entry, *statId));

    /* Finally install the field entry */
    OPENNSL_IF_ERROR_RETURN(opennsl_field_entry_install(unit, entry));

    printf
      ("  Policer %2d, Stat: %2d; CIR: %5d[%4d]; CBS: %5d[%4d]; PIR: %5d[%4d]; PBS: %5d[%4d]\n",
       policer_id, *statId, cir, cir / 8, cbs, cbs / 8, pir, pir / 8, pbs, pbs / 8);
    return OPENNSL_E_NONE;
}


/* Check Policer Rates
 *
 * This function attempts to compute actual data rates from policers defined
 * above. The assumption is that all ports are oversubscribed and that all
 * policer peak rates will be exceeded resulting in traffic shaping. The
 * computed rates are checked against expected rates. If the overall error
 * exceeds a empirically determined limit, an error status is returned.
 */
opennsl_error_t
example_check_rates(int unit, int *stat_list, int stat_count)
{
    const int   max_error = 50; /* 1/2 of 1% */
    const int   loop_count = 15;
    int         loop;
    int         accumulated_error = 0;

    for (loop = 0; loop < loop_count; loop++) {
        int         idx;
        const int   delay = 2;
        uint64      stat_value;

        sleep(delay);
        printf("\nLoop: %d\n", loop);
        for (idx = 0; idx < stat_count; idx++) {
            OPENNSL_IF_ERROR_RETURN(opennsl_field_stat_get
                                (unit, stat_list[idx], opennslFieldStatNotRedBytes,
                                 &stat_value));
            OPENNSL_IF_ERROR_RETURN(opennsl_field_stat_set
                                (unit, stat_list[idx], opennslFieldStatNotRedBytes, 0));
            /* First time around seems to always be off */
            if (loop > 0) {
                const int64   expected_rate = (((idx + 1) * 50) + 400) * 1000;
                const int64   rate = stat_value / delay;
                /* LSB= 0.01% */
                int64         rate_error =
                  ((rate - expected_rate) * 10000) / expected_rate;

                printf("Rate: %d = %8llu bytes/sec [expected=%8llu, error=%lld]\n",
                           stat_list[idx], rate, expected_rate, rate_error);
                accumulated_error += (rate_error < 0) ? -rate_error : rate_error;
            }
        }
    }
    accumulated_error /= (stat_count * (loop_count - 1));
    if (accumulated_error > max_error) {
        printf("FAIL: Per port avg error %d exceeds max of %d [LSB = 0.01%%]\n",
                   accumulated_error, max_error);
        return OPENNSL_E_FAIL;
    }
    printf("PASS: Per port avg error: +/- %d [LSB = 0.01%%]\n", accumulated_error);
    return OPENNSL_E_NONE;
}


/* Transmit a single test packet on the specified port */
static opennsl_error_t
example_tx_pkt(int unit, int port)
{
    uint8       mypkt[] = {

/*
  00    01    02    03    04    05    06    07    08    09    10    11    12    13    14    15*/
0x01, 0x00, 0x5E, 0x00, 0x00, 0x01, 0x80, 0x80, 0x80, 0x71, 0x35, 0x42, 0x81, 0x00, 0x00, 0x01,
0x08, 0x00, 0x45, 0x00, 0x00, 0x5A, 0x00, 0x01, 0x00, 0x00, 0x40, 0x11, 0xD7, 0xE6, 0xC0, 0xA8,
0x01, 0x01, 0xE0, 0x01, 0x01, 0x01, 0x00, 0x07, 0x00, 0x07, 0x00, 0x46, 0x2C, 0xF6, 0x41, 0x6C,
0x6C, 0x20, 0x47, 0x6F, 0x6F, 0x64, 0x20, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x20, 0x43, 0x6F,
0x6D, 0x65, 0x20, 0x54, 0x6F, 0x20, 0x54, 0x68, 0x6F, 0x73, 0x65, 0x20, 0x57, 0x68, 0x6F, 0x20,
0x57, 0x61, 0x6E, 0x74, 0x20, 0x4C, 0x6F, 0x74, 0x73, 0x20, 0x4F, 0x66, 0x20, 0x47, 0x6F, 0x6F,
0x64, 0x20, 0x54, 0x68, 0x69, 0x6E, 0x67, 0x73, 0x00, 0x00, 0x00, 0x00
    };
    const int   mypkt_SIZEOF = sizeof(mypkt);
    opennsl_pkt_t  *pkt;

    OPENNSL_IF_ERROR_RETURN(opennsl_pkt_alloc(unit, mypkt_SIZEOF, 0, &pkt));
    opennsl_pkt_memcpy(pkt, 0, mypkt, mypkt_SIZEOF);
    pkt->pkt_data->len = mypkt_SIZEOF;
    pkt->flags = OPENNSL_TX_CRC_REGEN;
    OPENNSL_PBMP_PORT_SET(pkt->tx_pbmp, port);

    /* Transmit packet */
    OPENNSL_IF_ERROR_RETURN(opennsl_tx(unit, pkt, NULL));

    OPENNSL_IF_ERROR_RETURN(opennsl_pkt_free(unit, pkt));
    return OPENNSL_E_NONE;
}


/* Create VLAN (if necessary) and add a port to it.
 * Strip VLAN tags on egressing traffic.
 */
static opennsl_error_t
example_add_port_to_vlan(int unit, opennsl_vlan_t vlan, opennsl_port_t port)
{
    opennsl_pbmp_t  untagged;;
    opennsl_pbmp_t  port_mask;
    opennsl_error_t rv;

    if (OPENNSL_FAILURE(rv = opennsl_vlan_create(unit, vlan)) && (rv != OPENNSL_E_EXISTS)) {
        printf("Failed to create VLAN %d\n", vlan);
        return rv;
    }
    OPENNSL_PBMP_PORT_SET(port_mask, port);
    OPENNSL_PBMP_PORT_SET(untagged, port);
    OPENNSL_IF_ERROR_RETURN(opennsl_vlan_port_add(unit, vlan, port_mask, untagged));
    OPENNSL_IF_ERROR_RETURN(opennsl_port_untagged_vlan_set(unit, port, vlan));
    return OPENNSL_E_NONE;
}


/*
 * This function configures two ports to feed back on each other when a packet
 * is sent on either one of them. This causes a "packet storm" on these two
 * ports resulting in a high rate of traffic on these ports.
 *
 * The traffic from the storm ports is used to generate traffic on other
 * ports. These ports will be configued such that ingressing traffic is
 * assigned to a unique VLAN. Policers will be created for these other ports
 * (called ingress ports).
 */
int example_policer_test(int unit)
{
    const opennsl_vlan_t vlan_base = 100;
    const int   max_ports = 10;
    const int   storm_ports = 2;

    opennsl_field_group_t group = -1;
    opennsl_port_config_t portConfig;
    opennsl_port_t  ingress_list[max_ports];
    opennsl_port_t  port;
    opennsl_port_t  port_list[max_ports];
    int         ingress_count;
    int         port_count;
    int         stat_ids[max_ports];

    port_count = 0;
    ingress_count = 0;
    OPENNSL_IF_ERROR_RETURN(opennsl_port_config_get(unit, &portConfig));
    OPENNSL_PBMP_ITER(portConfig.e, port) {
        if (port_count == max_ports) {
            break;
        }
        port_list[port_count] = port;
        OPENNSL_IF_ERROR_RETURN(opennsl_port_loopback_set(unit, port, OPENNSL_PORT_LOOPBACK_MAC));
        if (port_count >= storm_ports) {
            opennsl_vlan_t  next_vlan = (port_count >> 1) + vlan_base;
            /*
             * Once storm ports are configured, configure test port pairs
             * (ingress and egress). Each port in the pair will be assigned
             * to a VLAN. Untagged packets on these ports will be assigned
             * to the new VLAN. The egress port only belongs to the new
             * VLAN. The ingress port belongs to both the new VLAN and the
             * default VLAN. This allows it to receive all traffic broadcast
             * on the default VLAN from the storm ports. The egress port is
             * configured to drop all packets to prevent packet storms on
             * these port pairs.
             */
            OPENNSL_IF_ERROR_RETURN(example_add_port_to_vlan(unit, next_vlan, port));
            if (port_count & 1) {
                opennsl_pbmp_t  port_mask;

                OPENNSL_PBMP_PORT_SET(port_mask, port);
                /* Remove egress port from default VLAN */
                OPENNSL_IF_ERROR_RETURN(opennsl_vlan_port_remove(unit, 1, port_mask));
            } else {
                /* Set policer on ingress port */
                printf("Ingress Test Port: %d\n", port);
                OPENNSL_IF_ERROR_RETURN(example_create_policer
                                    (unit, &group, port, next_vlan,
                                     ingress_count, &stat_ids[ingress_count]));
                ingress_list[ingress_count] = port;
                ingress_count++;
            }
        }
        port_count++;
    }
    if (port_count != max_ports) {
        printf("Not enough ethernet ports for test: %d\n", port_count);
    }

    printf("Send packet on storm port %d\n", port_list[0]);
    /* Create a packet storm to fully subscribe all ports being tested */
    OPENNSL_IF_ERROR_RETURN(example_tx_pkt(unit, port_list[0]));
    OPENNSL_IF_ERROR_RETURN(example_check_rates(unit, stat_ids, ingress_count));

    return OPENNSL_E_NONE;
}


/*****************************************************************//**
 * \brief Main function for policer application
 *
 * \param argc, argv         commands line arguments
 *
 * \return OPENNSL_E_XXX     OpenNSL API return code
 ********************************************************************/
int main(int argc, char *argv[])
{
  int rv = 0;
  int unit = DEFAULT_UNIT;

  /* Initialize the system. */
  rv = opennsl_driver_init((opennsl_init_t *) NULL);

  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to initialize the system. Error: %s\r\n",
           opennsl_errmsg(rv));
    return rv;
  }

  /* cold boot initialization commands */
  rv = example_port_default_config(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to apply default config on ports, rc = %d (%s).\r\n",
           rv, opennsl_errmsg(rv));
  }

  /* Add ports to default vlan. */
  printf("Adding ports to default vlan.\r\n");
  rv = example_switch_default_vlan_config(unit);
  if(rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to add default ports. Error: %s\r\n",
        opennsl_errmsg(rv));
  }

  /* Create policer and test traffic rate */
  rv = example_policer_test(unit);
  if (rv != OPENNSL_E_NONE) {
    printf("\r\nFailed to test policer. Error: %s\r\n",
        opennsl_errmsg(rv));
  }  

  return rv;
}
