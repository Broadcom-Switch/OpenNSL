/** \addtogroup mirror Mirroring
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2015
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * 
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * 
 ***************************************************************************//**
 * \file			mirror.h
 ******************************************************************************/

#ifndef __OPENNSL_MIRROR_H__
#define __OPENNSL_MIRROR_H__

#include <opennsl/types.h>
#include <opennsl/pkt.h>

#define OPENNSL_MIRROR_DISABLE  0          /**< Disable mirroring. */
#define OPENNSL_MIRROR_L2       1          /**< Enable mirroring. */
#define OPENNSL_MIRROR_L2_L3    2          /**< Deprecated. */
#define OPENNSL_MIRROR_PORT_ENABLE      0x00000001 /**< Enable mirroring. */
#define OPENNSL_MIRROR_PORT_INGRESS     0x00000002 /**< Ingress mirroring. */
#define OPENNSL_MIRROR_PORT_EGRESS      0x00000004 /**< Egress mirroring. */
#define OPENNSL_MIRROR_PORT_EGRESS_TRUE 0x00000008 /**< True egress mirroring. */
#define OPENNSL_MIRROR_PORT_DEST_TRUNK  0x00000010 /**< Parameter dest_port is a
                                                      trunk. */
#define OPENNSL_MIRROR_PORT_EGRESS_ACL  0x00000020 /**< Enable Egress Mirroring
                                                      for ACLs */
#define OPENNSL_MIRROR_NIV_LOOP 1          /**< Mirrored packet is a loop in NIV
                                              path */
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the mirroring module to its initial configuration.
 *
 *\description Initializes the mirroring module. Mirroring is disabled on the
 *          device. .
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the current mirroring mode for the device.
 *
 *\description Enable or disable mirroring according to the mirror mode. This API
 *          function is intended to be used when the configuration of ONE (and
 *          only one) mirror-to-port per device is used, and in conjunction
 *          with opennsl_mirror_to_set. When enabling mirroring, the device is
 *          only configured after opennsl_mirror_to_set is called to set up
 *          the mirror-to-port.  If multiple mirror-to-port operation is
 *          needed, use opennsl_mirror_port_dest_add for switch family III
 *          switch chips and opennsl_mirror_to_pbmp_set for network switch
 *          fabric chips. Other switch chips do not support multiple
 *          mirror-to-ports. .
 *
 *\param    unit [IN]   Unit number.
 *\param    mode [IN]   OPENNSL Mirroring mode
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL On non switch family switch devices
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_mode_set(
    int unit, 
    int mode) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get the current mirroring mode for the device.
 *
 *\description Get the current mirroring mode for the device.
 *
 *\param    unit [IN]   Unit number.
 *\param    mode [OUT]   OPENNSL Mirroring mode
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_mode_get(
    int unit, 
    int *mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the mirror-to port for the device.
 *
 *\description Set the mirror-to port for the device. This API function set ONE
 *          (and only one) mirror-to-port per device.  If multiple
 *          mirror-to-port operation is needed, use
 *          opennsl_mirror_port_dest_add for switch family III switch chips
 *          and opennsl_mirror_to_pbmp_set for network switch fabric chips.
 *          Other switch chips do not support multiple mirror-to-ports.
 *          If the opennslSwitchDirectedMirroring switch control is disabled
 *          (or unsupported), the mirror-to port must be a member of the same
 *          VLANs as the mirrored port.
 *          If the opennslSwitchDirectedMirroring switch control is enabled,
 *          or the unit only supports directed mirroring, then
 *          OPENNSL_E_CONFIG will be returned.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number to mirror all ingress/egress
 *          selections to.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_CONFIG Operation not supported for directed mirroring
 *          configurations.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_to_set(
    int unit, 
    opennsl_port_t port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the mirror-to port for the device.
 *
 *\description Get the mirror-to port for the device. port = -1 if no mirror-to
 *          port has been set.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [OUT]   Device or logical port number to mirror all
 *          ingress/egress selections to.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_to_get(
    int unit, 
    opennsl_port_t *port) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable or Disable ingress mirroring for a port on the device.
 *
 *\description Enable or Disable the ingress mirroring for a port on the device.
 *          This call supersedes opennsl_port_mirror_enable_set. Mirroring
 *          must also be globally enabled using =opennsl_mirror_mode_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number to get ingress mirroring
 *          enable status on.
 *\param    val [IN]   Boolean value for on/off
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_INIT Module is not initialized.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_ingress_set(
    int unit, 
    opennsl_port_t port, 
    int val) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the ingress mirroring enabled/disabled status for a port on the
 *       device.
 *
 *\description Get the ingress mirroring enabled/disabled status for a port on
 *          the device. This call supersedes opennsl_port_mirror_enable_get.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number for which to retrieve
 *          ingress mirroring status.
 *\param    val [OUT]   Boolean value for on/off
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_INIT Module is not initialized.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_ingress_get(
    int unit, 
    opennsl_port_t port, 
    int *val) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable or Disable egress mirroring for a port on the device.
 *
 *\description Enable or Disable the egress mirroring for a port on the device.
 *          Mirroring must also be globally enabled using.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number to enable egress mirroring
 *          on.
 *\param    val [IN]   Boolean value for on/off
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_INIT Module is not initialized.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_egress_set(
    int unit, 
    opennsl_port_t port, 
    int val) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the egress mirroring enabled/disabled status for a port on the
 *       device.
 *
 *\description Get the egress mirroring enabled/disabled status for a port on the
 *          device.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number for which to retrieve egress
 *          mirroring status.
 *\param    val [OUT]   Boolean value for on/off
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID.
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_INIT Module is not initialized.
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_egress_get(
    int unit, 
    opennsl_port_t port, 
    int *val) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set mirroring configuration for a port.
 *
 *\description Configure a port to be mirrored on another port or trunk group.
 *          The mirror-to port or mirror mode can be changed by calling the
 *          _set function repetitively. For example: In case the mirroring
 *          mode is changed from, ingress to ingress+egress, both flags must
 *          be specified when the _set function is called the second time,
 *          that is, if only the egress flag is specified, the currently
 *          active ingress mirroring will be disabled.
 *          To disable mirroring of a port, set the flags parameter to 0
 *          (zero) in the _set command. In this case the mirror-to port
 *          parameters are ignored.
 *          If opennslSwitchDirectedMirroring is disabled for the unit and
 *          dest_mod is non-negative, then the dest_mod path is looked up
 *          using.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    dest_mod [IN]   Module ID of mirror-to port (-1 for local port)
 *\param    dest_port [IN]   Mirror-to port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_* flags
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_module_t dest_mod, 
    opennsl_port_t dest_port, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get mirroring configuration for a port.
 *
 *\description Get mirroring configuration for a port. If no flags are set when
 *          the function returns, the contents of the dest_* parameters is
 *          undefined.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to get configuration for
 *\param    dest_mod [OUT]   Module ID of mirror-to port
 *\param    dest_port [OUT]   Mirror-to port
 *\param    flags [OUT]   OPENNSL_MIRROR_PORT_* flags
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_module_t *dest_mod, 
    opennsl_port_t *dest_port, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add mirroring destination to a port.
 *
 *\description Add mirroring destination to a port. This API can be called
 *          multiple times on devices that support multiple mirror
 *          destinations per-port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    mirror_dest_id [IN]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_dest_add(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    opennsl_gport_t mirror_dest_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete mirroring destination from a port.
 *
 *\description Delete mirroring destination from a port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    mirror_dest_id [IN]
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_dest_delete(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    opennsl_gport_t mirror_dest_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all mirroring destinations from a port.
 *
 *\description Delete all mirroring destinations of the specified type(s) from a
 *          port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_dest_delete_all(
    int unit, 
    opennsl_port_t port, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get port mirroring destinations.
 *
 *\description Get port mirroring destinations. .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    mirror_dest_size [IN]   Size of allocated entries in mirror_dest
 *          array.
 *\param    mirror_dest [OUT]   Size of allocated entries in mirror_dest array.
 *\param    mirror_dest_count [OUT]   Actual number of mirror destinations.   This
 *          will be a value less than or equal to the value passed in as
 *          mirror_dest_size unless mirror_dest_size is 0.  If mirror_dest_size is
 *          0 then mirror_dest is ignored and mirror_dest_count is filled in with
 *          the number of entries that would have been filled into mirror_dest if
 *          mirror_dest_size was arbitrarily large.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_dest_get(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    int mirror_dest_size, 
    opennsl_gport_t *mirror_dest, 
    int *mirror_dest_count) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set mirroring configuration for a port-vlan.
 *
 *\description Configure a port-vlan to be mirrored on another port-vlan or trunk
 *          group. The mirror-to port-vlan or mirror mode can be changed by
 *          calling the _set function repetitively. For example: In case the
 *          mirroring mode is changed from, ingress to ingress+egress, both
 *          flags must be specified when the _set function is called the
 *          second time, that is, if only the egress flag is specified, the
 *          currently active ingress mirroring will be disabled.
 *          To disable mirroring of a port-vlan, set the flags parameter to 0
 *          (zero) in the _set command. In this case the mirror-to port-vlan
 *          parameters are ignored.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    vlan [IN]   Vlan number to configure
 *\param    destport [IN]   Mirror-to port
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_* flags
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    opennsl_gport_t destport, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get mirroring configuration for a port-vlan.
 *
 *\description Get mirroring configuration for a port-vlan. If no flags are set
 *          when the function returns, the contents of the dest_* parameters
 *          is undefined.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to get configuration for
 *\param    vlan [IN]   Vlan number to get configuration for
 *\param    dest_port [OUT]
 *\param    flags [OUT]   OPENNSL_MIRROR_PORT_* flags
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    opennsl_gport_t *dest_port, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Add mirroring destination to a port-vlan.
 *
 *\description Add mirroring destination to a port-vlan. This API can be called
 *          multiple times on devices that support multiple mirror
 *          destinations per-port-vlan.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    vlan [IN]   Mirrored vlan
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    destid [IN]   Destination GPORT Must be OPENNSL_GPORT_MIRROR.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_dest_add(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    uint32 flags, 
    opennsl_gport_t destid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete mirroring destination from a port-vlan.
 *
 *\description Delete mirroring destination from a port-vlan.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    vlan [IN]   Mirrored vlan
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    destid [IN]   Destination GPORT Must be OPENNSL_GPORT_MIRROR.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_dest_delete(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    uint32 flags, 
    opennsl_gport_t destid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Delete all mirroring destinations from a port-vlan.
 *
 *\description Delete all mirroring destinations of the specified type(s) from a
 *          port-vlan.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    vlan [IN]   Mirrored vlan
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_dest_delete_all(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get port-vlan mirroring destinations.
 *
 *\description Get port-vlan mirroring destinations. .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Mirrored port
 *\param    vlan [IN]   Mirrored vlan
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_*
 *\param    mirror_dest_size [IN]   Size of allocated entries in mirror_dest
 *          array.
 *\param    destid [OUT]   Array for mirror destinations information
 *\param    destcount [OUT]   Actual number of mirror destinations.   This will be
 *          a value less than or equal to the value passed in as mirror_dest_size
 *          unless mirror_dest_size is 0.  If mirror_dest_size is 0 then
 *          mirror_dest is ignored and mirror_dest_count is filled in with the
 *          number of entries that would have been filled into mirror_dest if
 *          mirror_dest_size was arbitrarily large.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_mirror_port_vlan_dest_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vlan, 
    uint32 flags, 
    uint32 mirror_dest_size, 
    opennsl_gport_t *destid, 
    uint32 *destcount) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** 
 * Mirror port Structure
 * 
 * Contains information required for mirror port settings.
 */
typedef struct opennsl_mirror_port_info_s {
    opennsl_gport_t mirror_system_id;   /**< Unique mirror System identifier. */
} opennsl_mirror_port_info_t;

/***************************************************************************//** 
 *\brief Initialize a mirror port information structure.
 *
 *\description Initialize a mirror port information structure.
 *
 *\param    info [IN,OUT]   Pointer to the struct to be initialized
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_mirror_port_info_t_init(
    opennsl_mirror_port_info_t *info) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set mirroring information per port.
 *
 *\description Set mirroring information per port, flags. Set System-mirror-ID
 *          per port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_* flags
 *\param    info [IN]   Mirror port information.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_info_set(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    opennsl_mirror_port_info_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get mirroring information per port.
 *
 *\description Get mirroring information per port, flags. .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number to configure
 *\param    flags [IN]   OPENNSL_MIRROR_PORT_* flags
 *\param    info [OUT]   Mirror port information.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNIT Invalid OPENNSL device ID
 *\retval    OPENNSL_E_PORT Invalid port
 *\retval    OPENNSL_E_XXX Other errors
 ******************************************************************************/
extern int opennsl_mirror_port_info_get(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    opennsl_mirror_port_info_t *info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#include <opennsl/mirrorX.h>
#endif /* __OPENNSL_MIRROR_H__ */
/*@}*/
