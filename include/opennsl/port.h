/** \addtogroup port Port Management
 *  @{
 */
/*****************************************************************************
 * 
 * (C) Copyright Broadcom Corporation 2013-2016
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
 * \file			port.h
 ******************************************************************************/

#ifndef __OPENNSL_PORT_H__
#define __OPENNSL_PORT_H__

#include <shared/portmode.h>
#include <shared/port.h>
#include <shared/phyconfig.h>
#include <shared/phyreg.h>
#include <shared/switch.h>
#include <opennsl/types.h>
#include <opennsl/stat.h>
#include <shared/port_ability.h>

#define OPENNSL_PIPES_MAX       _SHR_SWITCH_MAX_PIPES 
/** Port Configuration structure. */
typedef struct opennsl_port_config_s {
    opennsl_pbmp_t fe;                  /**< Mask of FE ports. */
    opennsl_pbmp_t ge;                  /**< Mask of GE ports. */
    opennsl_pbmp_t xe;                  /**< Mask of 10gig ports. */
    opennsl_pbmp_t ce;                  /**< Mask of 100gig ports. */
    opennsl_pbmp_t e;                   /**< Mask of eth ports. */
    opennsl_pbmp_t hg;                  /**< Mask of Higig ports. */
    opennsl_pbmp_t sci;                 /**< Mask of SCI ports. */
    opennsl_pbmp_t sfi;                 /**< Mask of SFI ports. */
    opennsl_pbmp_t spi;                 /**< Mask of SPI ports. */
    opennsl_pbmp_t spi_subport;         /**< Mask of SPI subports. */
    opennsl_pbmp_t port;                /**< Mask of all front panel ports. */
    opennsl_pbmp_t cpu;                 /**< Mask of CPU ports. */
    opennsl_pbmp_t all;                 /**< Mask of all ports. */
    opennsl_pbmp_t stack_int;           /**< Deprecated - unused. */
    opennsl_pbmp_t stack_ext;           /**< Mask of Stack ports. */
    opennsl_pbmp_t tdm;                 /**< Mask of TDM ports. */
    opennsl_pbmp_t pon;                 /**< Mask of PON ports. */
    opennsl_pbmp_t llid;                /**< Mask of LLID ports. */
    opennsl_pbmp_t il;                  /**< Mask of ILKN ports. */
    opennsl_pbmp_t xl;                  /**< Mask of XLAUI ports. */
    opennsl_pbmp_t rcy;                 /**< Mask of RECYCLE ports. */
    opennsl_pbmp_t per_pipe[OPENNSL_PIPES_MAX]; /**< Mask of ports per pipe. The number of
                                           pipes per device can be obtained via
                                           num_pipes field of opennsl_info_t. */
    opennsl_pbmp_t nif;                 /**< Mask of Network Interfaces ports. */
    opennsl_pbmp_t control;             /**< Mask of hot swap controlling ports. */
} opennsl_port_config_t;

/** Port ability */
typedef _shr_port_ability_t opennsl_port_ability_t;

#define OPENNSL_PORT_ABILITY_10MB           _SHR_PA_SPEED_10MB 
#define OPENNSL_PORT_ABILITY_100MB          _SHR_PA_SPEED_100MB 
#define OPENNSL_PORT_ABILITY_1000MB         _SHR_PA_SPEED_1000MB 
#define OPENNSL_PORT_ABILITY_2500MB         _SHR_PA_SPEED_2500MB 
#define OPENNSL_PORT_ABILITY_3000MB         _SHR_PA_SPEED_3000MB 
#define OPENNSL_PORT_ABILITY_5000MB         _SHR_PA_SPEED_5000MB 
#define OPENNSL_PORT_ABILITY_6000MB         _SHR_PA_SPEED_6000MB 
#define OPENNSL_PORT_ABILITY_10GB           _SHR_PA_SPEED_10GB 
#define OPENNSL_PORT_ABILITY_11GB           _SHR_PA_SPEED_11GB 
#define OPENNSL_PORT_ABILITY_12GB           _SHR_PA_SPEED_12GB 
#define OPENNSL_PORT_ABILITY_12P5GB         _SHR_PA_SPEED_12P5GB 
#define OPENNSL_PORT_ABILITY_13GB           _SHR_PA_SPEED_13GB 
#define OPENNSL_PORT_ABILITY_15GB           _SHR_PA_SPEED_15GB 
#define OPENNSL_PORT_ABILITY_16GB           _SHR_PA_SPEED_16GB 
#define OPENNSL_PORT_ABILITY_20GB           _SHR_PA_SPEED_20GB 
#define OPENNSL_PORT_ABILITY_21GB           _SHR_PA_SPEED_21GB 
#define OPENNSL_PORT_ABILITY_23GB           _SHR_PA_SPEED_23GB 
#define OPENNSL_PORT_ABILITY_24GB           _SHR_PA_SPEED_24GB 
#define OPENNSL_PORT_ABILITY_25GB           _SHR_PA_SPEED_25GB 
#define OPENNSL_PORT_ABILITY_27GB           _SHR_PA_SPEED_27GB 
#define OPENNSL_PORT_ABILITY_30GB           _SHR_PA_SPEED_30GB 
#define OPENNSL_PORT_ABILITY_32GB           _SHR_PA_SPEED_32GB 
#define OPENNSL_PORT_ABILITY_40GB           _SHR_PA_SPEED_40GB 
#define OPENNSL_PORT_ABILITY_42GB           _SHR_PA_SPEED_42GB 
#define OPENNSL_PORT_ABILITY_48GB           _SHR_PA_SPEED_48GB 
#define OPENNSL_PORT_ABILITY_50GB           _SHR_PA_SPEED_50GB 
#define OPENNSL_PORT_ABILITY_53GB           _SHR_PA_SPEED_53GB 
#define OPENNSL_PORT_ABILITY_100GB          _SHR_PA_SPEED_100GB 
#define OPENNSL_PORT_ABILITY_106GB          _SHR_PA_SPEED_106GB 
#define OPENNSL_PORT_ABILITY_120GB          _SHR_PA_SPEED_120GB 
#define OPENNSL_PORT_ABILITY_127GB          _SHR_PA_SPEED_127GB 
#define OPENNSL_PORT_ABILITY_INTERFACE_TBI  _SHR_PA_INTF_TBI 
#define OPENNSL_PORT_ABILITY_INTERFACE_MII  _SHR_PA_INTF_MII 
#define OPENNSL_PORT_ABILITY_INTERFACE_GMII _SHR_PA_INTF_GMII 
#define OPENNSL_PORT_ABILITY_INTERFACE_SGMII _SHR_PA_INTF_SGMII 
#define OPENNSL_PORT_ABILITY_INTERFACE_XGMII _SHR_PA_INTF_XGMII 
#define OPENNSL_PORT_ABILITY_INTERFACE_QSGMII _SHR_PA_INTF_QSGMII 
#define OPENNSL_PORT_ABILITY_INTERFACE_CGMII _SHR_PA_INTF_CGMII 
#define OPENNSL_PORT_ABILITY_MEDIUM_COPPER  _SHR_PA_MEDIUM_COPPER 
#define OPENNSL_PORT_ABILITY_MEDIUM_FIBER   _SHR_PA_MEDIUM_FIBER 
#define OPENNSL_PORT_ABILITY_LB_NONE        _SHR_PA_LB_NONE 
#define OPENNSL_PORT_ABILITY_LB_MAC         _SHR_PA_LB_MAC 
#define OPENNSL_PORT_ABILITY_LB_PHY         _SHR_PA_LB_PHY 
#define OPENNSL_PORT_ABILITY_LB_LINE        _SHR_PA_LB_LINE 
#define OPENNSL_PORT_ABILITY_AUTONEG        _SHR_PA_AUTONEG 
#define OPENNSL_PORT_ABILITY_COMBO          _SHR_PA_COMBO 
#define OPENNSL_PORT_ABILITY_PAUSE_TX       _SHR_PA_PAUSE_TX 
#define OPENNSL_PORT_ABILITY_PAUSE_RX       _SHR_PA_PAUSE_RX 
#define OPENNSL_PORT_ABILITY_PAUSE          _SHR_PA_PAUSE /**< Both TX and RX. */
#define OPENNSL_PORT_ABILITY_PAUSE_ASYMM    _SHR_PA_PAUSE_ASYMM /**< The following is used
                                                          only by
                                                          opennsl_port_ability_get,
                                                          and indicates that a
                                                          port can support
                                                          having PAUSE_TX be
                                                          different than
                                                          PAUSE_RX. */
#define OPENNSL_PORT_ABILITY_FEC_NONE       _SHR_PA_FEC_NONE /**< No FEC request */
#define OPENNSL_PORT_ABILITY_FEC_CL74       _SHR_PA_FEC_CL74 /**< FEC CL74  request. */
#define OPENNSL_PORT_ABILITY_FEC_CL91       _SHR_PA_FEC_CL91 /**< FEC CL91  request. */
#define OPENNSL_PORT_ABILITY_EEE_100MB_BASETX _SHR_PA_EEE_100MB_BASETX /**< EEE ability at
                                                          100M-BaseTX. */
#define OPENNSL_PORT_ABILITY_EEE_1GB_BASET  _SHR_PA_EEE_1GB_BASET /**< EEE ability at
                                                          1G-BaseT. */
#define OPENNSL_PORT_ABILITY_EEE_10GB_BASET _SHR_PA_EEE_10GB_BASET /**< EEE ability at
                                                          10G-BaseT. */
#define OPENNSL_PORT_ABILITY_EEE_10GB_KX    _SHR_PA_EEE_10GB_KX /**< EEE ability at
                                                          10GB-KX. */
#define OPENNSL_PORT_ABILITY_EEE_10GB_KX4   _SHR_PA_EEE_10GB_KX4 /**< EEE ability at
                                                          10GB-KX4. */
#define OPENNSL_PORT_ABILITY_EEE_10GB_KR    _SHR_PA_EEE_10GB_KR /**< EEE ability at
                                                          10GB-KR. */
/** 
 * Port ability mask.
 * 
 * The following flags are used to indicate which set of capabilities are
 * provided by a PHY or MAC when retrieving the ability of a port,
 * setting or getting the local advertisement, getting the remote
 * advertisement, or setting the MAC encapsulation and/or CRC modes.
 */
typedef _shr_port_mode_t opennsl_port_abil_t;

#define OPENNSL_PORT_ABIL_10MB_HD       _SHR_PM_10MB_HD 
#define OPENNSL_PORT_ABIL_10MB_FD       _SHR_PM_10MB_FD 
#define OPENNSL_PORT_ABIL_100MB_HD      _SHR_PM_100MB_HD 
#define OPENNSL_PORT_ABIL_100MB_FD      _SHR_PM_100MB_FD 
#define OPENNSL_PORT_ABIL_1000MB_HD     _SHR_PM_1000MB_HD 
#define OPENNSL_PORT_ABIL_1000MB_FD     _SHR_PM_1000MB_FD 
#define OPENNSL_PORT_ABIL_2500MB_HD     _SHR_PM_2500MB_HD 
#define OPENNSL_PORT_ABIL_2500MB_FD     _SHR_PM_2500MB_FD 
#define OPENNSL_PORT_ABIL_3000MB_HD     _SHR_PM_3000MB_HD 
#define OPENNSL_PORT_ABIL_3000MB_FD     _SHR_PM_3000MB_FD 
#define OPENNSL_PORT_ABIL_10GB_HD       _SHR_PM_10GB_HD 
#define OPENNSL_PORT_ABIL_10GB_FD       _SHR_PM_10GB_FD 
#define OPENNSL_PORT_ABIL_12GB_HD       _SHR_PM_12GB_HD 
#define OPENNSL_PORT_ABIL_12GB_FD       _SHR_PM_12GB_FD 
#define OPENNSL_PORT_ABIL_13GB_HD       _SHR_PM_13GB_HD 
#define OPENNSL_PORT_ABIL_13GB_FD       _SHR_PM_13GB_FD 
#define OPENNSL_PORT_ABIL_16GB_HD       _SHR_PM_16GB_HD 
#define OPENNSL_PORT_ABIL_16GB_FD       _SHR_PM_16GB_FD 
#define OPENNSL_PORT_ABIL_TBI           _SHR_PM_TBI 
#define OPENNSL_PORT_ABIL_MII           _SHR_PM_MII 
#define OPENNSL_PORT_ABIL_GMII          _SHR_PM_GMII 
#define OPENNSL_PORT_ABIL_SGMII         _SHR_PM_SGMII 
#define OPENNSL_PORT_ABIL_XGMII         _SHR_PM_XGMII 
#define OPENNSL_PORT_ABIL_LB_MAC        _SHR_PM_LB_MAC 
#define OPENNSL_PORT_ABIL_LB_PHY        _SHR_PM_LB_PHY 
#define OPENNSL_PORT_ABIL_LB_NONE       _SHR_PM_LB_NONE 
#define OPENNSL_PORT_ABIL_AN            _SHR_PM_AN 
#define OPENNSL_PORT_ABIL_COMBO         _SHR_PM_COMBO 
#define OPENNSL_PORT_ABIL_PAUSE_TX      _SHR_PM_PAUSE_TX 
#define OPENNSL_PORT_ABIL_PAUSE_RX      _SHR_PM_PAUSE_RX 
#define OPENNSL_PORT_ABIL_PAUSE         _SHR_PM_PAUSE /**< Both TX and RX. */
#define OPENNSL_PORT_ABIL_10B           OPENNSL_PORT_ABIL_TBI /**< Deprecated */
#define OPENNSL_PORT_ABIL_PAUSE_ASYMM   _SHR_PM_PAUSE_ASYMM /**< The following is used only
                                                      by
                                                      opennsl_port_ability_get,
                                                      and indicates that a port
                                                      can support having
                                                      PAUSE_TX be different than
                                                      PAUSE_RX. */
#define OPENNSL_PORT_ABIL_10MB          _SHR_PM_10MB 
#define OPENNSL_PORT_ABIL_100MB         _SHR_PM_100MB 
#define OPENNSL_PORT_ABIL_1000MB        _SHR_PM_1000MB 
#define OPENNSL_PORT_ABIL_2500MB        _SHR_PM_2500MB 
#define OPENNSL_PORT_ABIL_3000MB        _SHR_PM_3000MB 
#define OPENNSL_PORT_ABIL_10GB          _SHR_PM_10GB 
#define OPENNSL_PORT_ABIL_12GB          _SHR_PM_12GB 
#define OPENNSL_PORT_ABIL_13GB          _SHR_PM_13GB 
#define OPENNSL_PORT_ABIL_16GB          _SHR_PM_16GB 
#define OPENNSL_PORT_ABIL_HD            _SHR_PM_HD 
#define OPENNSL_PORT_ABIL_FD            _SHR_PM_FD 
#define OPENNSL_PORT_ABIL_SPD_ANY       _SHR_PM_SPEED_ALL 
#define OPENNSL_PORT_ABIL_SPD_MAX(abil)  \
    _SHR_PM_SPEED_MAX(abil) 
#define OPENNSL_PORT_ABILITY_SPEED_MAX(abil)  _SHR_PA_SPEED_MAX(abil) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Initialize the port subsystem.
 *
 *\description In initializes the port API subsystem. Initialization includes
 *          probing the types of ports on the unit, as well as any external
 *          phys. Internally PHY drivers are attached for the known found
 *          devices.  The initial configuration of the port and PHY state can
 *          be controlled through driver run-time configuration properties
 *          (see opennsl_port_settings_init).
 *          All port specific operating modes are placed in a known good
 *          state. Port initialization performs the following actions, but not
 *          all actions are supported on all chips:.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_port_init(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize the port subsystem without affecting the current state of
 *       stack ports.
 *
 *\description Clear the current port subsystem state for the specified device,
 *          without changing the state of stack link ports.  This function
 *          used in conjunction with the corresponding opennsl_xxx_clear APIs
 *          in other modules can be used to re-initialize a unit without
 *          causing a link status change on known stack ports.  This API can
 *          be used in conjunction with the Broadcom Stacking software to
 *          reset a unit into a known state after it has joined an existing
 *          stack.
 *
 *\param    unit [IN]   Unit number.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_clear(
    int unit) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Probe the port to determine the proper MAC and PHY drivers.
 *
 *\description Under normal conditions this routine should not be called.
 *          =opennsl_port_init performs this function during initialization.
 *          When used in conjunction with =opennsl_port_detach, systems that
 *          supports adding and removing external PHY devices must use this
 *          routine to probe and attached newly added PHYs. On successful
 *          probe, the port subsystem installs internal drivers for the PHYs
 *          allowing the rest of the configuration to be completed using the
 *          opennsl_port_xxx APIs.
 *          Calls made to the OPENNSL API on ports that have not been
 *          successfully probed are undefined and may have catastrophic
 *          results.
 *          All port state is undefined after an attach, and should be
 *          explicitly programmed.
 *
 *\param    unit [IN]   Unit number.
 *\param    pbmp [IN]   Port bit map indicating the ports to probe
 *\param    okay_pbmp [OUT]   Return value indicating the ports successfully
 *          probed
 *
 *\retval    OPENNSL_E_NONE All ports successfully probed. The value okay_pbmp
 *          contains a map of ports that may be enabled.
 *\retval    OPENNSL_E_INIT The Port module not initialized. See .
 *\retval    OPENNSL_E_XXX Failed to probe ports, the contents of okay_pbmp are
 *          undefined.
 ******************************************************************************/
extern int opennsl_port_probe(
    int unit, 
    opennsl_pbmp_t pbmp, 
    opennsl_pbmp_t *okay_pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Detach ports from the OPENNSL API.
 *
 *\description Detach a port from the port subsystem, configuring it such that
 *          the link state and other configuration routines behave as if the
 *          link is permanently down.
 *          This routine may be used to allow hot swapping of external PHY
 *          devices. If the external PHY is being swapped, the port must be
 *          detached to ensure OPENNSL API operations that query or change
 *          port state operate properly. When a new external PHY is installed,
 *          the port must be probed using =opennsl_port_probe to query the
 *          device and install the correct internal drivers for the device.
 *          It is the responsibility of the application to make the necessary
 *          changes to all other configuration settings  such as VLANS,
 *          multicast groups, and trunk configuration.
 *          for Trident2+, Apache, Firebolt, Maverick and its variants
 *          (portmod switches), a port needs to be removed from linkscan  if
 *          linkscan is enabled on the port before detaching it
 *          (opennsl_port_detach). .
 *
 *\param    unit [IN]   Unit number.
 *\param    pbmp [IN]   Port bit map of ports to be detached
 *\param    detached [OUT]   Port bit map of ports successfully detached.
 *
 *\retval    OPENNSL_E_OK Port successfully detached.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Port detach failed, considered a catastrophic error.
 ******************************************************************************/
extern int opennsl_port_detach(
    int unit, 
    opennsl_pbmp_t pbmp, 
    opennsl_pbmp_t *detached) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieved the port configuration for the specified device.
 *
 *\description opennsl_port_config_get returns all known ports configured on the
 *          specified device.
 *          The logical information indicates port bit maps to represent the
 *          ports on the specified unit (see the Broadcom Network Switching
 *          Stacking Guide for a description of logical port lists).
 *          =OPENNSL_PORT_CONFIG_t describes the meaning of each field.
 *
 *\param    unit [IN]   Unit number.
 *\param    config [OUT]   Pointer to port configuration structure populated on
 *          successful return.
 *
 *\retval    OPENNSL_E_NONE
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_config_get(
    int unit, 
    opennsl_port_config_t *config) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern char *opennsl_port_name(
    int unit, 
    int port) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Enable or disable a port.
 *
 *\description Controls whether a port is enabled or disabled for transmission
 *          and reception of packets.  The chip should not be configured so as
 *          to switch any packets to a disabled port because the packets may
 *          build up in the MMU.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    enable [IN]   Boolean value indicating enable (1) or disable (0).
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the current enabled
 *          state, the value of the parameter enable is undefined.
 ******************************************************************************/
extern int opennsl_port_enable_set(
    int unit, 
    opennsl_port_t port, 
    int enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable or disable a port.
 *
 *\description Controls whether a port is enabled or disabled for transmission
 *          and reception of packets.  The chip should not be configured so as
 *          to switch any packets to a disabled port because the packets may
 *          build up in the MMU.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    enable [OUT]   Boolean value indicating enable (1) or disable (0).
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the current enabled
 *          state, the value of the parameter enable is undefined.
 ******************************************************************************/
extern int opennsl_port_enable_get(
    int unit, 
    opennsl_port_t port, 
    int *enable) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]
 *\param    ability_mask [IN]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_port_advert_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_abil_t ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve auto-negotiation abilities for a port.
 *
 *\description Set or retrieve the current auto-negotiation abilities for the
 *          specified port. If the port is currently operating with
 *          auto-negotiation disabled, these settings will be programmed into
 *          the underlying devices but not have an affect until
 *          auto-negotiation is enabled. If auto-negotiation is enabled when
 *          the settings are changed, auto-negotiation must be restarted using
 *          =opennsl_port_autoneg_set .
 *          Setting or retrieving the currently set ability structure can be
 *          done at any time, including with auto-negotiation disabled. The
 *          setting will only take affect when auto-negotiation is enabled or
 *          restarted. See.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Physical or logical port to query or set information on.
 *\param    ability_mask [IN]   Extended abilities structure,
 *          =EXTENDED_PORT_ABILITY_s .
 *
 *\retval    OPENNSL_E_NONE Requested action performed.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_ability_advert_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_ability_t *ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]
 *\param    ability_mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_port_advert_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_abil_t *ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve auto-negotiation abilities for a port.
 *
 *\description Set or retrieve the current auto-negotiation abilities for the
 *          specified port. If the port is currently operating with
 *          auto-negotiation disabled, these settings will be programmed into
 *          the underlying devices but not have an affect until
 *          auto-negotiation is enabled. If auto-negotiation is enabled when
 *          the settings are changed, auto-negotiation must be restarted using
 *          =opennsl_port_autoneg_set .
 *          Setting or retrieving the currently set ability structure can be
 *          done at any time, including with auto-negotiation disabled. The
 *          setting will only take affect when auto-negotiation is enabled or
 *          restarted. See.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Physical or logical port to query or set information on.
 *\param    ability_mask [OUT]   Extended abilities structure,
 *          =EXTENDED_PORT_ABILITY_s .
 *
 *\retval    OPENNSL_E_NONE Requested action performed.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_ability_advert_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_ability_t *ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]
 *\param    ability_mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_port_advert_remote_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_abil_t *ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the valid abilities of a remote port.
 *
 *\description Retrieve the abilities of the specified remote port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Physical or logical port to query or set information on.
 *\param    ability_mask [OUT]
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_XXX Operation failed, the return value local_ability_mask is
 *          undefined.
 ******************************************************************************/
extern int opennsl_port_ability_remote_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_ability_t *ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]
 *\param    local_ability_mask [OUT]
 *
 *\retval   OPENNSL_E_xxx
 ******************************************************************************/
extern int opennsl_port_ability_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_abil_t *local_ability_mask) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Retrieve the valid abilities of a local port.
 *
 *\description Retrieve the abilities of the specified local port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Physical or logical port to query or set information on.
 *\param    local_ability_mask [OUT]   Extended ability structure 
 *          =EXTENDED_PORT_ABILITY_s
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_XXX Operation failed, the return value local_ability_mask is
 *          undefined.
 ******************************************************************************/
extern int opennsl_port_ability_local_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_ability_t *local_ability_mask) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set the default VLAN for packets that ingress untagged.
 *
 *\description All packets that ingress a port untagged are treated as if they
 *          were tagged with the value specified by
 *          opennsl_port_untagged_vlan_set. All ports are initially configured
 *          with the untagged VLAN set to the default VLAN (or VLAN 1). If the
 *          packet egresses on a port that is configured as a tagged port, the
 *          VLAN ID in the egressing packet is set to this value.
 *          If the (port,vid) resolves to a VLAN gport, untagged packets will
 *          be sent to the to the VLAN port, and not the default VLAN. 
 *          Similarly, if (port,vid) resolves to a MPLS gport, untagged
 *          packets will be sent to the MPLS port and not to the default VLAN.
 *           In either case, the value does not affect the egress behavior of
 *          packets.
 *          To affect egress behavior of a VLAN gport, a GPORT ID is passed as
 *          the  port parameter.  The vid is used as the untagged vid on
 *          ingress into a PEP.  Specifically, when an STAG only packet
 *          arrives on a provider port, and egresses a customer port, the
 *          given vid is added to the untagged packet on egress.
 *          These APIs can also be used for WLAN gports. They will set/get the
 *          default  VLAN for untagged packets coming in from a WLAN source
 *          port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number or logical device
 *\param    vid [IN]   VLAN ID used for packets that ingress the port untagged.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL The specified port cannot have an untagged VLAN.
 *\retval    OPENNSL_E_PARAM Invalid port or VLAN ID.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_untagged_vlan_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t vid) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the default VLAN for packets that ingress untagged.
 *
 *\description All packets that ingress a port untagged are treated as if they
 *          were tagged with the value specified by
 *          opennsl_port_untagged_vlan_set. All ports are initially configured
 *          with the untagged VLAN set to the default VLAN (or VLAN 1). If the
 *          packet egresses on a port that is configured as a tagged port, the
 *          VLAN ID in the egressing packet is set to this value.
 *          If the (port,vid) resolves to a VLAN gport, untagged packets will
 *          be sent to the to the VLAN port, and not the default VLAN. 
 *          Similarly, if (port,vid) resolves to a MPLS gport, untagged
 *          packets will be sent to the MPLS port and not to the default VLAN.
 *           In either case, the value does not affect the egress behavior of
 *          packets.
 *          To affect egress behavior of a VLAN gport, a GPORT ID is passed as
 *          the  port parameter.  The vid is used as the untagged vid on
 *          ingress into a PEP.  Specifically, when an STAG only packet
 *          arrives on a provider port, and egresses a customer port, the
 *          given vid is added to the untagged packet on egress.
 *          These APIs can also be used for WLAN gports. They will set/get the
 *          default  VLAN for untagged packets coming in from a WLAN source
 *          port.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number or logical device
 *\param    vid_ptr [OUT]   Pointer to location to store current default VLAN ID.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL The specified port cannot have an untagged VLAN.
 *\retval    OPENNSL_E_PARAM Invalid port or VLAN ID.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_untagged_vlan_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_vlan_t *vid_ptr) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the default priority for packets that ingress untagged.
 *
 *\description All packets that ingress a port untagged are treated as if they
 *          were tagged with the value specified by
 *          opennsl_port_untagged_priority_set. This priority is used
 *          regardless of any ARL entry match.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number or logical device
 *\param    priority [IN]   Priority to assign to packets that ingress the port
 *          untagged. A negative value here has special meaning to certain SoC
 *          devices.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL The specified port cannot have an untagged priority.
 *\retval    OPENNSL_E_PARAM Invalid port or priority.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_untagged_priority_set(
    int unit, 
    opennsl_port_t port, 
    int priority) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the default priority for packets that ingress untagged.
 *
 *\description All packets that ingress a port untagged are treated as if they
 *          were tagged with the value specified by
 *          opennsl_port_untagged_priority_set. This priority is used
 *          regardless of any ARL entry match.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port number or logical device
 *\param    priority [OUT]   Priority to assign to packets that ingress the port
 *          untagged. A negative value here has special meaning to certain SoC
 *          devices.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL The specified port cannot have an untagged priority.
 *\retval    OPENNSL_E_PARAM Invalid port or priority.
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_untagged_priority_get(
    int unit, 
    opennsl_port_t port, 
    int *priority) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_DSCP_MAP_NONE          0          /**< Disable DSCP mapping */
#define OPENNSL_PORT_DSCP_MAP_ZERO          1          /**< Map only if incoming
                                                          DSCP = 0. */
#define OPENNSL_PORT_DSCP_MAP_ALL           2          /**< Map all. */
#define OPENNSL_PORT_DSCP_MAP_UNTAGGED_ONLY 3          /**< Map only when packet
                                                          is untagged. */
#define OPENNSL_PORT_DSCP_MAP_DEFAULT       4          /**< Map according to
                                                          default mapping,Not
                                                          looking at PCP or TOS. */
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Control mapping of Differentiated Services Code Points (DSCP).
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    mode [IN]   DSCP map mode.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Invalid mapping mode
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_dscp_map_mode_set(
    int unit, 
    opennsl_port_t port, 
    int mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control mapping of Differentiated Services Code Points (DSCP).
 *
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    mode [OUT]   DSCP map mode.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Invalid mapping mode
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_dscp_map_mode_get(
    int unit, 
    opennsl_port_t port, 
    int *mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control mapping of Differentiated Services Code Points (DSCP).
 *
 *\description Incoming IPv4 format packets have Differentiated Services Code
 *          Points in their type of service (ToS) header field.  DSCP values
 *          are small integers from 0 to 63.
 *          Some switch devices have the capability of rewriting incoming code
 *          points into other mapped code points for use within the switching
 *          domain.  Some switch devices also have the capability of setting
 *          the internal priority and drop precedence based on the source
 *          DSCP.
 *          The allowable values for the input parameters may be limited by
 *          the device's underlying hardware capabilities.
 *          switch family?and switch familySwitch switches allow a limited
 *          number of DSCP mapping possibilities: for these devices srccp can
 *          be -1 or 0 only. These devices do not perform DSCP-based priority
 *          mapping.
 *          The network switch family of switches use the
 *          OPENNSL_PRIO_RED(DP=3), OPENNSL_PRIO_YELLOW(DP=2),
 *          OPENNSL_PRIO_GREEN(DP=1),  OPENNSL_PRIO_PRESERVE /
 *          OPENNSL_PRIO_DROP_LAST(DP=0) ored with prio to configure  the drop
 *          precedence (DP) value. For network switch B0 family that supports
 *          ECN mapping, OPENNSL_DSCP_ECN can be ored with srccp to the
 *          designated {DSCP(7:2):ECN(1:0)}.
 *          A port value of -1 or gport type for system configuration will
 *          configure all ports.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number or -1 to setup global
 *          mapping table.
 *\param    srccp [IN]   Source code point. -1 indicates operation applies to all
 *          code points if being configured or a random code point if being
 *          retrieved.
 *\param    mapcp [IN]   The new code point to map srccp to if setting the
 *          mapping; the currently configured mapping for the port if retrieving
 *          settings.
 *\param    prio [IN]   Priority of packets mapped for the code point, if
 *          available. Priority is 0 to 7 and can have the value
 *          (OPENNSL_PRIO_RED/OPENNSL_PRIO_YELLOW/OPENNSL_PRIO_GREEN/OPENNSL_PRIO_PRESERVE)
 *          ored in. -1 on get means priority mapping is unavailable.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Source or mapped code point values are invalid.
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device, or
 *          mapping resources depleted.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_dscp_map_set(
    int unit, 
    opennsl_port_t port, 
    int srccp, 
    int mapcp, 
    int prio) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control mapping of Differentiated Services Code Points (DSCP).
 *
 *\description Incoming IPv4 format packets have Differentiated Services Code
 *          Points in their type of service (ToS) header field.  DSCP values
 *          are small integers from 0 to 63.
 *          Some switch devices have the capability of rewriting incoming code
 *          points into other mapped code points for use within the switching
 *          domain.  Some switch devices also have the capability of setting
 *          the internal priority and drop precedence based on the source
 *          DSCP.
 *          The allowable values for the input parameters may be limited by
 *          the device's underlying hardware capabilities.
 *          switch family?and switch familySwitch switches allow a limited
 *          number of DSCP mapping possibilities: for these devices srccp can
 *          be -1 or 0 only. These devices do not perform DSCP-based priority
 *          mapping.
 *          The network switch family of switches use the
 *          OPENNSL_PRIO_RED(DP=3), OPENNSL_PRIO_YELLOW(DP=2),
 *          OPENNSL_PRIO_GREEN(DP=1),  OPENNSL_PRIO_PRESERVE /
 *          OPENNSL_PRIO_DROP_LAST(DP=0) ored with prio to configure  the drop
 *          precedence (DP) value. For network switch B0 family that supports
 *          ECN mapping, OPENNSL_DSCP_ECN can be ored with srccp to the
 *          designated {DSCP(7:2):ECN(1:0)}.
 *          A port value of -1 or gport type for system configuration will
 *          configure all ports.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number or -1 to setup global
 *          mapping table.
 *\param    srccp [IN]   Source code point. -1 indicates operation applies to all
 *          code points if being configured or a random code point if being
 *          retrieved.
 *\param    mapcp [OUT]   The new code point to map srccp to if setting the
 *          mapping; the currently configured mapping for the port if retrieving
 *          settings.
 *\param    prio [OUT]   Priority of packets mapped for the code point, if
 *          available. Priority is 0 to 7 and can have the value
 *          (OPENNSL_PRIO_RED/OPENNSL_PRIO_YELLOW/OPENNSL_PRIO_GREEN/OPENNSL_PRIO_PRESERVE)
 *          ored in. -1 on get means priority mapping is unavailable.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Source or mapped code point values are invalid.
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device, or
 *          mapping resources depleted.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_dscp_map_get(
    int unit, 
    opennsl_port_t port, 
    int srccp, 
    int *mapcp, 
    int *prio) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current linkscan mode for the specified port.
 *
 *\description Link scanning is performed by the linkscan task ( =linkscan). For
 *          the OPENNSL interface, these functions are equivalent to functions
 *          =opennsl_linkscan_mode_set and =opennsl_linkscan_mode_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    linkscan [IN]   Linkscan mode, see table =OPENNSL_LINKSCAN_MODE_e
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Invalid linkscan mode specified
 *\retval    OPENNSL_E_UNAVAIL Requested operating mode is not supported.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_linkscan_set(
    int unit, 
    opennsl_port_t port, 
    int linkscan) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current linkscan mode for the specified port.
 *
 *\description Link scanning is performed by the linkscan task ( =linkscan). For
 *          the OPENNSL interface, these functions are equivalent to functions
 *          =opennsl_linkscan_mode_set and =opennsl_linkscan_mode_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    linkscan [OUT]   Linkscan mode, see table =OPENNSL_LINKSCAN_MODE_e
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_PARAM Invalid linkscan mode specified
 *\retval    OPENNSL_E_UNAVAIL Requested operating mode is not supported.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_linkscan_get(
    int unit, 
    opennsl_port_t port, 
    int *linkscan) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure or retrieve the current auto-negotiation settings for a port,
 *       or restart auto-negotiation if already enabled.
 *
 *\description Enable, disable, or recover the current auto-negotiation state for
 *          a port. If auto-negotiation is already enabled, re-enabling it
 *          will restart auto-negotiation.
 *          Before enabling auto-negotiation, the desired advertised modes
 *          must be configured using =opennsl_port_advert_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    autoneg [IN]   0 for disable, 1 for enabled
 *
 *\retval    OPENNSL_E_NONE Operation performed. If retrieving current
 *          auto-negotiation mode, autoneg is set to the current state.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation fail, if retrieving current operating mode,
 *          autoneg is undefined.
 ******************************************************************************/
extern int opennsl_port_autoneg_set(
    int unit, 
    opennsl_port_t port, 
    int autoneg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure or retrieve the current auto-negotiation settings for a port,
 *       or restart auto-negotiation if already enabled.
 *
 *\description Enable, disable, or recover the current auto-negotiation state for
 *          a port. If auto-negotiation is already enabled, re-enabling it
 *          will restart auto-negotiation.
 *          Before enabling auto-negotiation, the desired advertised modes
 *          must be configured using =opennsl_port_advert_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    autoneg [OUT]   0 for disable, 1 for enabled
 *
 *\retval    OPENNSL_E_NONE Operation performed. If retrieving current
 *          auto-negotiation mode, autoneg is set to the current state.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation fail, if retrieving current operating mode,
 *          autoneg is undefined.
 ******************************************************************************/
extern int opennsl_port_autoneg_get(
    int unit, 
    opennsl_port_t port, 
    int *autoneg) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current operating speed of a port.
 *
 *\description Set or get the speed of the specified port. opennsl_port_speed_set
 *          disables auto-negotiation if it is enabled. When setting a speed,
 *          if an error is returned the PHY and the MAC may not be properly
 *          set for operation. A value of 0 indicates, set max speed. For
 *          correct operation  following an error, a valid speed must be set.
 *          When retrieving the current speed of a port, if auto-negotiation
 *          is enabled the current negotiated speed is returned. If
 *          auto-negotiation is in progress or there is no link, speed
 *          returned is undefined. If auto-negotiation is disabled, the forced
 *          speed of the port is returned regardless of the link state.
 *          opennsl_port_speed_max returns the maximum possible operating
 *          speed of the port based on the attributes of the MAC and the PHY.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    speed [OUT]   Speed specified in Mbps.
 *
 *\retval    OPENNSL_E_NONE Speed set or retrieved as requested.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_CONFIG The requested port speed is not supported. In some
 *          configurations the actual speed of the MAC is derived from the PHY
 *          directly and can not be forced to a specific value.
 *\retval    OPENNSL_E_XXX Error occurred, if retrieving port speed, the returned
 *          speed is undefined. If setting speed, the operational state of the
 *          port is undefined.
 ******************************************************************************/
extern int opennsl_port_speed_max(
    int unit, 
    opennsl_port_t port, 
    int *speed) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current operating speed of a port.
 *
 *\description Set or get the speed of the specified port. opennsl_port_speed_set
 *          disables auto-negotiation if it is enabled. When setting a speed,
 *          if an error is returned the PHY and the MAC may not be properly
 *          set for operation. A value of 0 indicates, set max speed. For
 *          correct operation  following an error, a valid speed must be set.
 *          When retrieving the current speed of a port, if auto-negotiation
 *          is enabled the current negotiated speed is returned. If
 *          auto-negotiation is in progress or there is no link, speed
 *          returned is undefined. If auto-negotiation is disabled, the forced
 *          speed of the port is returned regardless of the link state.
 *          opennsl_port_speed_max returns the maximum possible operating
 *          speed of the port based on the attributes of the MAC and the PHY.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    speed [IN]   Speed specified in Mbps.
 *
 *\retval    OPENNSL_E_NONE Speed set or retrieved as requested.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_CONFIG The requested port speed is not supported. In some
 *          configurations the actual speed of the MAC is derived from the PHY
 *          directly and can not be forced to a specific value.
 *\retval    OPENNSL_E_XXX Error occurred, if retrieving port speed, the returned
 *          speed is undefined. If setting speed, the operational state of the
 *          port is undefined.
 ******************************************************************************/
extern int opennsl_port_speed_set(
    int unit, 
    opennsl_port_t port, 
    int speed) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current operating speed of a port.
 *
 *\description Set or get the speed of the specified port. opennsl_port_speed_set
 *          disables auto-negotiation if it is enabled. When setting a speed,
 *          if an error is returned the PHY and the MAC may not be properly
 *          set for operation. A value of 0 indicates, set max speed. For
 *          correct operation  following an error, a valid speed must be set.
 *          When retrieving the current speed of a port, if auto-negotiation
 *          is enabled the current negotiated speed is returned. If
 *          auto-negotiation is in progress or there is no link, speed
 *          returned is undefined. If auto-negotiation is disabled, the forced
 *          speed of the port is returned regardless of the link state.
 *          opennsl_port_speed_max returns the maximum possible operating
 *          speed of the port based on the attributes of the MAC and the PHY.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    speed [OUT]   Speed specified in Mbps.
 *
 *\retval    OPENNSL_E_NONE Speed set or retrieved as requested.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_CONFIG The requested port speed is not supported. In some
 *          configurations the actual speed of the MAC is derived from the PHY
 *          directly and can not be forced to a specific value.
 *\retval    OPENNSL_E_XXX Error occurred, if retrieving port speed, the returned
 *          speed is undefined. If setting speed, the operational state of the
 *          port is undefined.
 ******************************************************************************/
extern int opennsl_port_speed_get(
    int unit, 
    opennsl_port_t port, 
    int *speed) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_port_if_t */
typedef _shr_port_if_t opennsl_port_if_t;

#define OPENNSL_PORT_IF_NOCXN       _SHR_PORT_IF_NOCXN 
#define OPENNSL_PORT_IF_NULL        _SHR_PORT_IF_NULL 
#define OPENNSL_PORT_IF_MII         _SHR_PORT_IF_MII /**< MII Operating mode, not
                                                  supported on all ports */
#define OPENNSL_PORT_IF_GMII        _SHR_PORT_IF_GMII /**< GMII Operating mode, not
                                                  supported on all ports */
#define OPENNSL_PORT_IF_SGMII       _SHR_PORT_IF_SGMII 
#define OPENNSL_PORT_IF_TBI         _SHR_PORT_IF_TBI /**< TBI interface supported on
                                                  Gigabit Ethernet ports
                                                  operating at gigabit speeds */
#define OPENNSL_PORT_IF_XGMII       _SHR_PORT_IF_XGMII /**< 10-Gigabit interface */
#define OPENNSL_PORT_IF_RGMII       _SHR_PORT_IF_RGMII /**< Reduced Gigabit Media
                                                  Independent Interface */
#define OPENNSL_PORT_IF_SFI         _SHR_PORT_IF_SFI /**< SFI 10-Gigabit serial
                                                  electrical interface */
#define OPENNSL_PORT_IF_XFI         _SHR_PORT_IF_XFI /**< XFI 10-Gigabit serial
                                                  electrical interface */
#define OPENNSL_PORT_IF_KR          _SHR_PORT_IF_KR /**< Backplane 10 GbE 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_KR2         _SHR_PORT_IF_KR2 /**< Backplane 2x10GbE 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_KR4         _SHR_PORT_IF_KR4 /**< Backplane 4x10 GbE 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_CR          _SHR_PORT_IF_CR /**< Copper 10 GbE 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_CR2         _SHR_PORT_IF_CR2 /**< Copper 2x10GbE 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_CR4         _SHR_PORT_IF_CR4 /**< Copper 4x10 GbE 64B/66B
                                                  interface. */
#define OPENNSL_PORT_IF_XLAUI       _SHR_PORT_IF_XLAUI /**< 40 Gigabit Attachment Unit
                                                  Interface */
#define OPENNSL_PORT_IF_XLAUI2      _SHR_PORT_IF_XLAUI2 /**< 40 Gigabit Attachment Unit
                                                  Interface over 2 lanes */
#define OPENNSL_PORT_IF_RXAUI       _SHR_PORT_IF_RXAUI 
#define OPENNSL_PORT_IF_XAUI        _SHR_PORT_IF_XAUI 
#define OPENNSL_PORT_IF_SPAUI       _SHR_PORT_IF_SPAUI 
#define OPENNSL_PORT_IF_QSGMII      _SHR_PORT_IF_QSGMII 
#define OPENNSL_PORT_IF_ILKN        _SHR_PORT_IF_ILKN 
#define OPENNSL_PORT_IF_RCY         _SHR_PORT_IF_RCY 
#define OPENNSL_PORT_IF_FAT_PIPE    _SHR_PORT_IF_FAT_PIPE 
#define OPENNSL_PORT_IF_SR          _SHR_PORT_IF_SR /**< Fiber SR/LR 64B/66B interface */
#define OPENNSL_PORT_IF_SR2         _SHR_PORT_IF_SR2 /**< Fiber 2x10GbE 64B/66B
                                                  interface. */
#define OPENNSL_PORT_IF_CAUI        _SHR_PORT_IF_CAUI 
#define OPENNSL_PORT_IF_LR          _SHR_PORT_IF_LR /**< Fiber LR 64B/66B interface */
#define OPENNSL_PORT_IF_LR4         _SHR_PORT_IF_LR4 /**< Fiber LR4 64B/66B interface */
#define OPENNSL_PORT_IF_SR4         _SHR_PORT_IF_SR4 /**< Fiber SR4 64B/66B interface */
#define OPENNSL_PORT_IF_KX          _SHR_PORT_IF_KX 
#define OPENNSL_PORT_IF_ZR          _SHR_PORT_IF_ZR /**< Fiber ZR 64B/66B interface */
#define OPENNSL_PORT_IF_SR10        _SHR_PORT_IF_SR10 /**< Fiber SR10 64B/66B interface. */
#define OPENNSL_PORT_IF_CR10        _SHR_PORT_IF_CR10 /**< Copper CR10 64B/66B interface. */
#define OPENNSL_PORT_IF_KR10        _SHR_PORT_IF_KR10 /**< Backplane KR10 64B/66B
                                                  interface. */
#define OPENNSL_PORT_IF_LR10        _SHR_PORT_IF_LR10 /**< Fiber LR10 64B/66B interface. */
#define OPENNSL_PORT_IF_OTL         _SHR_PORT_IF_OTL /**< Fiber 4x25 GbE OTL interface */
#define OPENNSL_PORT_IF_CPU         _SHR_PORT_IF_CPU 
#define OPENNSL_PORT_IF_ER          _SHR_PORT_IF_ER /**< Fiber ER 64B/66B interface */
#define OPENNSL_PORT_IF_ER2         _SHR_PORT_IF_ER2 /**< Fiber ER2 2x10G 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_ER4         _SHR_PORT_IF_ER4 /**< Fiber ER4 4x10G 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_CX          _SHR_PORT_IF_CX /**< Copper 10G 10B/8B interface */
#define OPENNSL_PORT_IF_CX2         _SHR_PORT_IF_CX2 /**< Copper 2x10G 10B/8B interface. */
#define OPENNSL_PORT_IF_CX4         _SHR_PORT_IF_CX4 /**< Copper 4x10G 10B/8B interface */
#define OPENNSL_PORT_IF_CAUI_C2C    _SHR_PORT_IF_CAUI_C2C /**< CAUI 100G C2C interface */
#define OPENNSL_PORT_IF_CAUI_C2M    _SHR_PORT_IF_CAUI_C2M /**< CAUI 100G C2M interface */
#define OPENNSL_PORT_IF_VSR         _SHR_PORT_IF_VSR /**< Fiber VSR 10G 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_LR2         _SHR_PORT_IF_LR2 /**< Fiber 2x10Gbe LR 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_LRM         _SHR_PORT_IF_LRM /**< Fiber LRM multipoint 64B/66B
                                                  interface */
#define OPENNSL_PORT_IF_XLPPI       _SHR_PORT_IF_XLPPI /**< 40G parallel physical
                                                  interface */
#define OPENNSL_PORT_IF_LBG         _SHR_PORT_IF_LBG /**< Link bonding interface */
#define OPENNSL_PORT_IF_CAUI4       _SHR_PORT_IF_CAUI4 /**< CAUI4 100G interface */
#define OPENNSL_PORT_IF_COUNT       _SHR_PORT_IF_COUNT 
#define OPENNSL_PORT_IF_10B     OPENNSL_PORT_IF_TBI /**< Deprecated */
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Configure the physical interface between the MAC and the PHY for the
 *       specified port.
 *
 *\description Provides ability to change the physical interface used between the
 *          MAC in the switch device and the PHY. Under normal conditions this
 *          setting will be configured during port initialization and should
 *          not change. This function is provided for diagnostic purposes
 *          only. For information on initial physical interface settings, see.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    intf [IN]   Interface to configure or retrieved interface setting.
 *
 *\retval    OPENNSL_E_NONE Operation performed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_UNAVAIL Requested interface is not available on the
 *          specified port.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current operating mode
 *          result value in intf is undefined.
 ******************************************************************************/
extern int opennsl_port_interface_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_if_t intf) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure the physical interface between the MAC and the PHY for the
 *       specified port.
 *
 *\description Provides ability to change the physical interface used between the
 *          MAC in the switch device and the PHY. Under normal conditions this
 *          setting will be configured during port initialization and should
 *          not change. This function is provided for diagnostic purposes
 *          only. For information on initial physical interface settings, see.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    intf [OUT]   Interface to configure or retrieved interface setting.
 *
 *\retval    OPENNSL_E_NONE Operation performed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_UNAVAIL Requested interface is not available on the
 *          specified port.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current operating mode
 *          result value in intf is undefined.
 ******************************************************************************/
extern int opennsl_port_interface_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_if_t *intf) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_port_duplex_t */
typedef _shr_port_duplex_t opennsl_port_duplex_t;

#define OPENNSL_PORT_DUPLEX_HALF    _SHR_PORT_DUPLEX_HALF 
#define OPENNSL_PORT_DUPLEX_FULL    _SHR_PORT_DUPLEX_FULL 
#define OPENNSL_PORT_DUPLEX_COUNT   _SHR_PORT_DUPLEX_COUNT 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set the current duplex mode of a port.
 *
 *\description Set or get the duplex of the specified port.
 *          opennsl_port_duplex_set disables auto-negotiation if it is
 *          enabled. When setting duplicity, if an error is returned the PHY
 *          and the MAC may not be properly set for operation. For correct
 *          operation following an error, a valid duplex and speed must be
 *          set.
 *          When retrieving the current duplicity of a port, if
 *          auto-negotiation is enabled the current negotiated duplicity is
 *          returned. If auto-negotiation is in progress or there is no link,
 *          duplex is returned as OPENNSL_PORT_DUPLEX_HALF. If
 *          auto-negotiation is disabled, the forced speed of the port is
 *          returned regardless of the link state.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    duplex [IN]   Returned or requested duplex setting, must be one of
 *          OPENNSL_PORT_DUPLEX_HALF or OPENNSL_PORT_DUPLEX_FULL.
 *
 *\retval    OPENNSL_E_NONE Port duplex retrieved or configured as requested.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_UNAVAIL The specified port does not support the requested
 *          mode.
 *\retval    OPENNSL_E_XXX Request failed, if configuring duplex mode the port
 *          state is undefined. If retrieving the current operating mode, the
 *          returned duplex value is undefined.
 ******************************************************************************/
extern int opennsl_port_duplex_set(
    int unit, 
    opennsl_port_t port, 
    int duplex) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the current duplex mode of a port.
 *
 *\description Set or get the duplex of the specified port.
 *          opennsl_port_duplex_set disables auto-negotiation if it is
 *          enabled. When setting duplicity, if an error is returned the PHY
 *          and the MAC may not be properly set for operation. For correct
 *          operation following an error, a valid duplex and speed must be
 *          set.
 *          When retrieving the current duplicity of a port, if
 *          auto-negotiation is enabled the current negotiated duplicity is
 *          returned. If auto-negotiation is in progress or there is no link,
 *          duplex is returned as OPENNSL_PORT_DUPLEX_HALF. If
 *          auto-negotiation is disabled, the forced speed of the port is
 *          returned regardless of the link state.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    duplex [OUT]   Returned or requested duplex setting, must be one of
 *          OPENNSL_PORT_DUPLEX_HALF or OPENNSL_PORT_DUPLEX_FULL.
 *
 *\retval    OPENNSL_E_NONE Port duplex retrieved or configured as requested.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_UNAVAIL The specified port does not support the requested
 *          mode.
 *\retval    OPENNSL_E_XXX Request failed, if configuring duplex mode the port
 *          state is undefined. If retrieving the current operating mode, the
 *          returned duplex value is undefined.
 ******************************************************************************/
extern int opennsl_port_duplex_get(
    int unit, 
    opennsl_port_t port, 
    int *duplex) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable or disable transmission of pause frames and honoring received
 *       pause frames on a port.
 *
 *\description Depending on the port type, transmissions of pause frames and
 *          honoring received pause frames may be configured independently. If
 *          configuring independently (also known as asymmetric flow control)
 *          pause_tx and pause_rx need not be the same value. The API call
 *          =opennsl_port_ability_get can be used to determine if asymmetric
 *          pause is supported.  Symmetric flow control, where both
 *          transmission of pause frames and honoring them on reception can be
 *          enable or disable by passing 1 or 0 for both pause_tx and
 *          pause_rx, respectively.
 *          Generally asymmetric flow control is used to limit data flow from
 *          end stations toward the device, however if the underlying hardware
 *          supports it, opennsl_port_pause_set will allow configuring the
 *          device for asymmetric flow control in either direction.
 *          The current settings of pause-based flow control can be determined
 *          using opennsl_port_pause_get.
 *          Configuration of asymmetric flow control may also be accomplished
 *          using the API call =opennsl_port_pause_sym_set .
 *          Code samples demonstrating two methods to configure the same flow
 *          control settings can be found in the description of
 *          =opennsl_port_pause_sym_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port or logical port number
 *\param    pause_tx [IN]   0 to disable transmission of pauseframes, 1 to enable.
 *\param    pause_rx [IN]   0 to ignore received pause frames, 1 to honor received
 *          pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation performed successfully.
 *\retval    OPENNSL_E_INIT Port module not initialized ( must be called).
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current pause settings,
 *          pause_tx and pause_rx are undefined.
 ******************************************************************************/
extern int opennsl_port_pause_set(
    int unit, 
    opennsl_port_t port, 
    int pause_tx, 
    int pause_rx) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Enable or disable transmission of pause frames and honoring received
 *       pause frames on a port.
 *
 *\description Depending on the port type, transmissions of pause frames and
 *          honoring received pause frames may be configured independently. If
 *          configuring independently (also known as asymmetric flow control)
 *          pause_tx and pause_rx need not be the same value. The API call
 *          =opennsl_port_ability_get can be used to determine if asymmetric
 *          pause is supported.  Symmetric flow control, where both
 *          transmission of pause frames and honoring them on reception can be
 *          enable or disable by passing 1 or 0 for both pause_tx and
 *          pause_rx, respectively.
 *          Generally asymmetric flow control is used to limit data flow from
 *          end stations toward the device, however if the underlying hardware
 *          supports it, opennsl_port_pause_set will allow configuring the
 *          device for asymmetric flow control in either direction.
 *          The current settings of pause-based flow control can be determined
 *          using opennsl_port_pause_get.
 *          Configuration of asymmetric flow control may also be accomplished
 *          using the API call =opennsl_port_pause_sym_set .
 *          Code samples demonstrating two methods to configure the same flow
 *          control settings can be found in the description of
 *          =opennsl_port_pause_sym_set .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device port or logical port number
 *\param    pause_tx [OUT]   0 to disable transmission of pauseframes, 1 to
 *          enable.
 *\param    pause_rx [OUT]   0 to ignore received pause frames, 1 to honor
 *          received pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation performed successfully.
 *\retval    OPENNSL_E_INIT Port module not initialized ( must be called).
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current pause settings,
 *          pause_tx and pause_rx are undefined.
 ******************************************************************************/
extern int opennsl_port_pause_get(
    int unit, 
    opennsl_port_t port, 
    int *pause_tx, 
    int *pause_rx) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the source MAC address transmitted in MAC control pause
 *       frames.
 *
 *\description MAC control pause frames are transmitted with a well known
 *          destination address (01:80:c2:00:00:01) that is not controllable.
 *          However, the source address can be set and retrieved using the
 *          opennsl_port_pause_addr_xxx calls. On switch initialization, the
 *          application software should set the pause frame source address for
 *          all ports. These values are persistent across calls that enable or
 *          disable the transmission of pause frames and need only be set
 *          once.
 *          Only MAC control pause frames generated by the MACs in the switch
 *          device will contain the specified source address. The CPU is able
 *          to generate MAC control packets with any source address that will
 *          be transmitted unchanged.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number.
 *\param    mac [IN]   MAC address to transmit as the source address in MAC
 *          control pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the previously set
 *          values the returned MAC address is undefined.
 ******************************************************************************/
extern int opennsl_port_pause_addr_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_mac_t mac) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set the source MAC address transmitted in MAC control pause
 *       frames.
 *
 *\description MAC control pause frames are transmitted with a well known
 *          destination address (01:80:c2:00:00:01) that is not controllable.
 *          However, the source address can be set and retrieved using the
 *          opennsl_port_pause_addr_xxx calls. On switch initialization, the
 *          application software should set the pause frame source address for
 *          all ports. These values are persistent across calls that enable or
 *          disable the transmission of pause frames and need only be set
 *          once.
 *          Only MAC control pause frames generated by the MACs in the switch
 *          device will contain the specified source address. The CPU is able
 *          to generate MAC control packets with any source address that will
 *          be transmitted unchanged.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number.
 *\param    mac [OUT]   MAC address to transmit as the source address in MAC
 *          control pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the previously set
 *          values the returned MAC address is undefined.
 ******************************************************************************/
extern int opennsl_port_pause_addr_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_mac_t mac) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure or retrieve asymmetric pause setting for a port.
 *
 *\description For complete description, see.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pause [IN]   Requested or current pause settings, one of
 *          OPENNSL_PORT_PAUSE_SYM for symmetric pause, OPENNSL_PORT_PAUSE_ASYM_RX
 *          for asymmetric pause to honor received MAC control pause frames but
 *          not transmit, OPENNSL_PORT_PAUSE_ASYM_TX to ignore received pause
 *          frames but transmit, and OPENNSL_PORT_PAUSE_NONE to neither honor or
 *          transmit pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current mode the
 *          returned pause value is undefined.
 ******************************************************************************/
extern int opennsl_port_pause_sym_set(
    int unit, 
    opennsl_port_t port, 
    int pause) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure or retrieve asymmetric pause setting for a port.
 *
 *\description For complete description, see.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pause [OUT]   Requested or current pause settings, one of
 *          OPENNSL_PORT_PAUSE_SYM for symmetric pause, OPENNSL_PORT_PAUSE_ASYM_RX
 *          for asymmetric pause to honor received MAC control pause frames but
 *          not transmit, OPENNSL_PORT_PAUSE_ASYM_TX to ignore received pause
 *          frames but transmit, and OPENNSL_PORT_PAUSE_NONE to neither honor or
 *          transmit pause frames.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving current mode the
 *          returned pause value is undefined.
 ******************************************************************************/
extern int opennsl_port_pause_sym_get(
    int unit, 
    opennsl_port_t port, 
    int *pause) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set or retrieve the current maximum packet size permitted on a port.
 *
 *\description Set or retrieve the current maximum frame size for the specified
 *          port. The frame size may be different for ports supporting
 *          multiple speeds. For this reason, whenever the speed of a port
 *          changes the frame size should be set to the desired length.
 *          This API can be used to enable jumbo frames on a port by setting
 *          the frame size to a jumbo value.
 *          When setting the frame size on a port, it is the callers
 *          responsibility to take into account any additional tags or CRC
 *          that may be added by the switch device. For example, when
 *          configuring HiGig ports or stacking ports on some devices, a HiGig
 *          header or stack tag may be added to the packets.
 *          For front-panel ports (that is, non-stacking or HiGig ports),
 *          setting the maximum frame size to X indicates packets of length X
 *          + 4 are permitted.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port to set or retrieve maximum frame size on
 *\param    size [IN]   The frame size to set (or current frame size returned) in
 *          bytes.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, current frame size for port is
 *          undefined.
 ******************************************************************************/
extern int opennsl_port_frame_max_set(
    int unit, 
    opennsl_port_t port, 
    int size) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve the current maximum packet size permitted on a port.
 *
 *\description Set or retrieve the current maximum frame size for the specified
 *          port. The frame size may be different for ports supporting
 *          multiple speeds. For this reason, whenever the speed of a port
 *          changes the frame size should be set to the desired length.
 *          This API can be used to enable jumbo frames on a port by setting
 *          the frame size to a jumbo value.
 *          When setting the frame size on a port, it is the callers
 *          responsibility to take into account any additional tags or CRC
 *          that may be added by the switch device. For example, when
 *          configuring HiGig ports or stacking ports on some devices, a HiGig
 *          header or stack tag may be added to the packets.
 *          For front-panel ports (that is, non-stacking or HiGig ports),
 *          setting the maximum frame size to X indicates packets of length X
 *          + 4 are permitted.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port to set or retrieve maximum frame size on
 *\param    size [OUT]   The frame size to set (or current frame size returned) in
 *          bytes.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, current frame size for port is
 *          undefined.
 ******************************************************************************/
extern int opennsl_port_frame_max_get(
    int unit, 
    opennsl_port_t port, 
    int *size) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_PHY_CLAUSE45   _SHR_PORT_PHY_CLAUSE45 
#define OPENNSL_PORT_PHY_CLAUSE45_ADDR(_devad, _regad)  \
    _SHR_PORT_PHY_CLAUSE45_ADDR(_devad, _regad) 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Read or write PHY registers associated with a port.
 *
 *\description Most PHY-related operations are performed automatically by the API
 *          to satisfy requests. When direct access to the PHY registers are
 *          required for diagnostic purposes or special configuration these
 *          functions can be used. Use of these routines may interfere with
 *          the normal operation of the API, extreme care must be taken when
 *          manipulating PHYs. Normal configuration of speed, duplicity, and
 *          auto-negotiation must be performed using the normal opennsl_port
 *          APIs. .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    flags [IN]   Flags indicating how to access the PHY, and which PHY if
 *          the port has an internal serdes. See =OPENNSL_PORT_PHY_flags for
 *          details.
 *\param    phy_reg_addr [IN]   Register address in the PHY
 *\param    phy_data [IN]   Data to be written or data read
 *\param    phy_mask [IN]   Mask write data when modifying register
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Requested operation not supported
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_phy_modify(
    int unit, 
    opennsl_port_t port, 
    uint32 flags, 
    uint32 phy_reg_addr, 
    uint32 phy_data, 
    uint32 phy_mask) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** MDI crossover control. */
typedef _shr_port_mdix_t opennsl_port_mdix_t;

#define OPENNSL_PORT_MDIX_AUTO          _SHR_PORT_MDIX_AUTO 
#define OPENNSL_PORT_MDIX_FORCE_AUTO    _SHR_PORT_MDIX_FORCE_AUTO 
#define OPENNSL_PORT_MDIX_NORMAL        _SHR_PORT_MDIX_NORMAL 
#define OPENNSL_PORT_MDIX_XOVER         _SHR_PORT_MDIX_XOVER 
#define OPENNSL_PORT_MDIX_COUNT         _SHR_PORT_MDIX_COUNT 
/** MDI crossover status. */
typedef _shr_port_mdix_status_t opennsl_port_mdix_status_t;

#define OPENNSL_PORT_MDIX_STATUS_NORMAL _SHR_PORT_MDIX_STATUS_NORMAL 
#define OPENNSL_PORT_MDIX_STATUS_XOVER  _SHR_PORT_MDIX_STATUS_XOVER 
#define OPENNSL_PORT_MDIX_STATUS_COUNT  _SHR_PORT_MDIX_STATUS_COUNT 
/** Combo port control/status. */
typedef _shr_port_medium_t opennsl_port_medium_t;

#define OPENNSL_PORT_MEDIUM_NONE    _SHR_PORT_MEDIUM_NONE 
#define OPENNSL_PORT_MEDIUM_COPPER  _SHR_PORT_MEDIUM_COPPER 
#define OPENNSL_PORT_MEDIUM_FIBER   _SHR_PORT_MEDIUM_FIBER 
#define OPENNSL_PORT_MEDIUM_COUNT   _SHR_PORT_MEDIUM_COUNT 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set the spanning tree state for a port (single instance spanning tree
 *       only).
 *
 *\description Used only if there is a single instance of spanning tree running,
 *          these functions get and set the spanning tree state for a port.
 *          These routines do not interoperate with the multiple spanning tree
 *          support defined in =stg . The application must use either
 *          opennsl_port_stp_set and opennsl_port_spt_get or the multiple
 *          spanning tree support routines exclusively.
 *          No check is made for using both methods simultaneously and the
 *          results are undefined.
 *          On many switch devices, no distinction is made between the
 *          BLOCKING and LISTENING states. For this reason
 *          OPENNSL_STG_STP_BLOCK and OPENNSL_STG_STP_LISTEN should be
 *          considered equivalent when calling these APIs. For example,
 *          setting a port in BLOCKING state using:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    state [IN]   Spanning tree state, for valid values see
 *          =OPENNSL_STG_STP_e .
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device. This
 *          occurs on fabric devices.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_stp_set(
    int unit, 
    opennsl_port_t port, 
    int state) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set the spanning tree state for a port (single instance spanning tree
 *       only).
 *
 *\description Used only if there is a single instance of spanning tree running,
 *          these functions get and set the spanning tree state for a port.
 *          These routines do not interoperate with the multiple spanning tree
 *          support defined in =stg . The application must use either
 *          opennsl_port_stp_set and opennsl_port_spt_get or the multiple
 *          spanning tree support routines exclusively.
 *          No check is made for using both methods simultaneously and the
 *          results are undefined.
 *          On many switch devices, no distinction is made between the
 *          BLOCKING and LISTENING states. For this reason
 *          OPENNSL_STG_STP_BLOCK and OPENNSL_STG_STP_LISTEN should be
 *          considered equivalent when calling these APIs. For example,
 *          setting a port in BLOCKING state using:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    state [OUT]   Spanning tree state, for valid values see
 *          =OPENNSL_STG_STP_e .
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device. This
 *          occurs on fabric devices.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_stp_get(
    int unit, 
    opennsl_port_t port, 
    int *state) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_LEARN_ARL      0x01       /**< Learn SLF address. */
#define OPENNSL_PORT_LEARN_CPU      0x02       /**< Copy SLF packet to CPU. */
#define OPENNSL_PORT_LEARN_FWD      0x04       /**< Forward SLF packet */
#define OPENNSL_PORT_LEARN_PENDING  0x08       /**< Mark learned SLF as pending */
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Control the hardware and software learning support on a port.
 *
 *\description The learning mode configures what set of actions are taken by the
 *          device when an unknown source address is recognized on an
 *          ingressing packet. Each of the learning options can be configured
 *          independently, however the underlying switch device may not
 *          support all combinations. The possible learning modes are
 *          described in =OPENNSL_PORT_LEARN_table .
 *          opennsl_port_learn_set and opennsl_port_learn_get get and set the
 *          current learning mode based on the flags parameter.
 *          opennsl_port_learn_modify allows learning options to be removed
 *          and or added based on the add and remove parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    flags [IN]   Learning flags as defined in table
 *          =OPENNSL_PORT_LEARN_table
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_UNAVAIL Requested learning configuration not supported on
 *          device, the learning mode of the port is unchanged.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, port state undefined on set or modify,
 *          returned flags value undefined if retrieving status.
 ******************************************************************************/
extern int opennsl_port_learn_set(
    int unit, 
    opennsl_port_t port, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control the hardware and software learning support on a port.
 *
 *\description The learning mode configures what set of actions are taken by the
 *          device when an unknown source address is recognized on an
 *          ingressing packet. Each of the learning options can be configured
 *          independently, however the underlying switch device may not
 *          support all combinations. The possible learning modes are
 *          described in =OPENNSL_PORT_LEARN_table .
 *          opennsl_port_learn_set and opennsl_port_learn_get get and set the
 *          current learning mode based on the flags parameter.
 *          opennsl_port_learn_modify allows learning options to be removed
 *          and or added based on the add and remove parameters.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port
 *\param    flags [OUT]   Learning flags as defined in table
 *          =OPENNSL_PORT_LEARN_table
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_UNAVAIL Requested learning configuration not supported on
 *          device, the learning mode of the port is unchanged.
 *\retval    OPENNSL_E_INIT Port module not initialized, see .
 *\retval    OPENNSL_E_XXX Operation failed, port state undefined on set or modify,
 *          returned flags value undefined if retrieving status.
 ******************************************************************************/
extern int opennsl_port_learn_get(
    int unit, 
    opennsl_port_t port, 
    uint32 *flags) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_LINK_STATUS_UP 1          
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Retrieve the current link status of a port.
 *
 *\description This call returns the link status of the port. With linkscan
 *          running (see =linkscan ), the current link status is retrieved
 *          from the linkscan task. This is the normal mode of operation, as
 *          link status in the PHY registers is latched low. If multiple
 *          sources (threads) read the physical link status in the PHY
 *          register, the linkscan task and/or applications can miss a link
 *          down event.
 *          If linkscan is not running, the current link status is retrieved
 *          from the PHY directly.
 *          The possible values of status are:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number.
 *\param    status [OUT]   One of OPENNSL_PORT_LINK_STATUS_*.
 *
 *\retval    OPENNSL_E_NONE Current link state is returned in status
 *\retval    OPENNSL_E_INIT Port module not initialized
 *\retval    OPENNSL_E_XXX Error condition reported from lower layers of software.
 *          In the event of an error code other than OPENNSL_E_NONE, the up
 *          parameter is undefined on return.
 ******************************************************************************/
extern int opennsl_port_link_status_get(
    int unit, 
    opennsl_port_t port, 
    int *status) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Clear failed link status from a port which has undergone LAG failover.
 *
 *\description This function clears the OPENNSL_PORT_LINK_STATUS_FAILED state
 *          from a port which has transitioned into LAG failover.  The port is
 *          moved to the OPENNSL_PORT_LINK_STATUS_DOWN state.  The application
 *          is responsible for removing the port from trunk membership before
 *          calling this function.  Linkscan (see =linkscan) must be running
 *          to use LAG failover.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *
 *\retval    OPENNSL_E_NONE The failed state of the port is cleared.
 *\retval    OPENNSL_E_INIT Linkscan module not initialized
 *\retval    OPENNSL_E_PORT The port is not valid, not in failed state, or still in
 *          the trunk.
 ******************************************************************************/
extern int opennsl_port_link_failed_clear(
    int unit, 
    opennsl_port_t port) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_VLAN_MEMBER_INGRESS    0x00000001 
#define OPENNSL_PORT_VLAN_MEMBER_EGRESS     0x00000002 
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set or retrieve current behavior of tagged packets arriving/leaving on a
 *       port not a member of the specified VLAN.
 *
 *\description Ingress/egress filtering, if enabled, drops all packets
 *          arriving/leaving on a  port with a VLAN tag identifying a VLAN of
 *          which the port is not a member. If disabled, packets will not be
 *          dropped if the port is not a member of the VLAN specified in the
 *          packet. It may however be dropped for other reasons such as
 *          spanning tree state, head of line blocking etc. For switch
 *          family?III, ingress filtering is also applied.
 *          Virtual Port(VP) will be assigned to a VP group or removed from a
 *          VP group through this API when filtering is enabled or disabled if
 *          flag OPENNSL_PORT_VLAN_MEMBER_VP_VLAN_MEMBERSHIP is not set.  So
 *          if user uses un-managed VP group mechanism, API
 *          =opennsl_port_control_set() with 
 *          opennslPortControlVlanVpGroupEgress/opennslPortControlVlanVpGroupIngress
 *          type should be called before =opennsl_port_vlan_member_set(). And
 *          if user use managed VP group mechanism,
 *          =opennsl_port_vlan_member_set should be called before API
 *          =opennsl_vlan_gport_add . Please refer to the DESCRIPTION of
 *          =opennsl_vlan_gport_add for more detail about VP group .
 *          This function supersedes =opennsl_port_ifilter_get . Valid
 *          settings for flags are described in
 *          =OPENNSL_PORT_VLAN_MEMBER_FLAGS_table .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    flags [IN]   Flags to indicate port filtering mode
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_vlan_member_set(
    int unit, 
    opennsl_port_t port, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve current behavior of tagged packets arriving/leaving on a
 *       port not a member of the specified VLAN.
 *
 *\description Ingress/egress filtering, if enabled, drops all packets
 *          arriving/leaving on a  port with a VLAN tag identifying a VLAN of
 *          which the port is not a member. If disabled, packets will not be
 *          dropped if the port is not a member of the VLAN specified in the
 *          packet. It may however be dropped for other reasons such as
 *          spanning tree state, head of line blocking etc. For switch
 *          family?III, ingress filtering is also applied.
 *          Virtual Port(VP) will be assigned to a VP group or removed from a
 *          VP group through this API when filtering is enabled or disabled if
 *          flag OPENNSL_PORT_VLAN_MEMBER_VP_VLAN_MEMBERSHIP is not set.  So
 *          if user uses un-managed VP group mechanism, API
 *          =opennsl_port_control_set() with 
 *          opennslPortControlVlanVpGroupEgress/opennslPortControlVlanVpGroupIngress
 *          type should be called before =opennsl_port_vlan_member_set(). And
 *          if user use managed VP group mechanism,
 *          =opennsl_port_vlan_member_set should be called before API
 *          =opennsl_vlan_gport_add . Please refer to the DESCRIPTION of
 *          =opennsl_vlan_gport_add for more detail about VP group .
 *          This function supersedes =opennsl_port_ifilter_get . Valid
 *          settings for flags are described in
 *          =OPENNSL_PORT_VLAN_MEMBER_FLAGS_table .
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    flags [OUT]   Flags to indicate port filtering mode
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on underlying device
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_vlan_member_get(
    int unit, 
    opennsl_port_t port, 
    uint32 *flags) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get the current count of cells or packets queued on a port for
 *       transmission.
 *
 *\description Returns a count that is either the number of internal device cells
 *          (device specific) or the number of packets queued for egress on
 *          the specified port. In general, the count returned should only be
 *          considered as 0 (indicating there are no packets queued on the
 *          port) or >0 (indicating some packets are queued on the port).
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number.
 *\param    count [OUT]   Returned count of cells or packets queued for egress on
 *          the specified port.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_BADID Invalid port number specified
 *\retval    OPENNSL_E_UNAVIL Operation not supported on the specified port.
 ******************************************************************************/
extern int opennsl_port_queued_count_get(
    int unit, 
    opennsl_port_t port, 
    uint32 *count) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Configure ports to block or allow packets from a given ingress port.
 *
 *\description This API controls the ability of a specific ingress port on a
 *          specific module to send packets to a local egress port.
 *          The specified modid is derived from the modid of port.
 *          For opennsl_port_egress_set, if port is -1 or gport type for
 *          system configuration, the configuration is applied to all source
 *          ports on the specified module.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical source port number.
 *\param    modid [IN]   Module ID of the source port.
 *\param    pbmp [IN]   Port bitmap indicating all local ports allowed to egress
 *          traffic from specified port/modid.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_UNAVAIL The specified port does not support the requested
 *          block option.
 *\retval    OPENNSL_E_PARAM Invalid port, module ID or bitmap.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_egress_set(
    int unit, 
    opennsl_port_t port, 
    int modid, 
    opennsl_pbmp_t pbmp) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Configure ports to block or allow packets from a given ingress port.
 *
 *\description This API controls the ability of a specific ingress port on a
 *          specific module to send packets to a local egress port.
 *          The specified modid is derived from the modid of port.
 *          For opennsl_port_egress_set, if port is -1 or gport type for
 *          system configuration, the configuration is applied to all source
 *          ports on the specified module.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical source port number.
 *\param    modid [IN]   Module ID of the source port.
 *\param    pbmp [OUT]   Port bitmap indicating all local ports allowed to egress
 *          traffic from specified port/modid.
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_UNAVAIL The specified port does not support the requested
 *          block option.
 *\retval    OPENNSL_E_PARAM Invalid port, module ID or bitmap.
 *\retval    OPENNSL_E_XXX Operation failed.
 ******************************************************************************/
extern int opennsl_port_egress_get(
    int unit, 
    opennsl_port_t port, 
    int modid, 
    opennsl_pbmp_t *pbmp) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_FLOOD_BLOCK_BCAST      0x1        
#define OPENNSL_PORT_FLOOD_BLOCK_UNKNOWN_UCAST 0x2        
#define OPENNSL_PORT_FLOOD_BLOCK_UNKNOWN_MCAST 0x4        
#define OPENNSL_PORT_FLOOD_BLOCK_ALL        0x8        
#define OPENNSL_PORT_FLOOD_BLOCK_UNKNOWN_IP_MCAST 0x10       
#define OPENNSL_PORT_FLOOD_BLOCK_UNKNOWN_NONIP_MCAST 0x20       
#define OPENNSL_PORT_FLOOD_BLOCK_KNOWN_MCAST 0x40       
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Selectively block flooding traffic.
 *
 *\description Selectively block VLAN flooding traffic ingressing on ingress_port
 *          from egressing on egress_port. The types of flooding traffic that
 *          can be selectively blocked are described in table.
 *
 *\param    unit [IN]   Unit number.
 *\param    ingress_port [IN]   Device or logical port number of the ingress port
 *\param    egress_port [IN]   Device or logical port number of the egress port
 *\param    flags [IN]
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on specified device
 *\retval    OPENNSL_E_PARAM ingress_port and egress_port are not on the same
 *          device
 *\retval    OPENNSL_E_PORT Operation not supported on the specified ingress_port,
 *          or egress_port is invalid
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_flood_block_set(
    int unit, 
    opennsl_port_t ingress_port, 
    opennsl_port_t egress_port, 
    uint32 flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Selectively block flooding traffic.
 *
 *\description Selectively block VLAN flooding traffic ingressing on ingress_port
 *          from egressing on egress_port. The types of flooding traffic that
 *          can be selectively blocked are described in table.
 *
 *\param    unit [IN]   Unit number.
 *\param    ingress_port [IN]   Device or logical port number of the ingress port
 *\param    egress_port [IN]   Device or logical port number of the egress port
 *\param    flags [OUT]
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Operation not supported on specified device
 *\retval    OPENNSL_E_PARAM ingress_port and egress_port are not on the same
 *          device
 *\retval    OPENNSL_E_PORT Operation not supported on the specified ingress_port,
 *          or egress_port is invalid
 *\retval    OPENNSL_E_XXX Operation failed
 ******************************************************************************/
extern int opennsl_port_flood_block_get(
    int unit, 
    opennsl_port_t ingress_port, 
    opennsl_port_t egress_port, 
    uint32 *flags) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control the sampling of packets ingressing or egressing a port.
 *
 *\description The Packet Sampling APIs are building blocks that can be used to
 *          implement the sFlow specification (RFC 3176).  switch family?III
 *          chips can select a random sampling of ingressing or egressing
 *          packets and send them to the CPU for profiling purposes.
 *          There are also three related switch control parameters to support
 *          the implementation of sFlow; see =opennsl_switch_control_set and.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    ingress_rate [IN]   Every 1/ingress_rate ingressing packets will be
 *          sampled; 0 indicates no sampling while 1 indicates sampling all
 *          packets
 *\param    egress_rate [IN]   Every 1/egress_rate egressing packets will be
 *          sampled; 0 indicates no sampling while 1 indicates sampling all
 *          packets
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported by hardware
 *\retval    OPENNSL_E_XXX Other error
 ******************************************************************************/
extern int opennsl_port_sample_rate_set(
    int unit, 
    opennsl_port_t port, 
    int ingress_rate, 
    int egress_rate) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Control the sampling of packets ingressing or egressing a port.
 *
 *\description The Packet Sampling APIs are building blocks that can be used to
 *          implement the sFlow specification (RFC 3176).  switch family?III
 *          chips can select a random sampling of ingressing or egressing
 *          packets and send them to the CPU for profiling purposes.
 *          There are also three related switch control parameters to support
 *          the implementation of sFlow; see =opennsl_switch_control_set and.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    ingress_rate [OUT]   Every 1/ingress_rate ingressing packets will be
 *          sampled; 0 indicates no sampling while 1 indicates sampling all
 *          packets
 *\param    egress_rate [OUT]   Every 1/egress_rate egressing packets will be
 *          sampled; 0 indicates no sampling while 1 indicates sampling all
 *          packets
 *
 *\retval    OPENNSL_E_UNAVAIL Feature not supported by hardware
 *\retval    OPENNSL_E_XXX Other error
 ******************************************************************************/
extern int opennsl_port_sample_rate_get(
    int unit, 
    opennsl_port_t port, 
    int *ingress_rate, 
    int *egress_rate) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_DTAG_MODE_NONE     0          /**< No double tagging. */
#define OPENNSL_PORT_DTAG_MODE_INTERNAL 1          /**< Service Provider port. */
#define OPENNSL_PORT_DTAG_MODE_EXTERNAL 2          /**< Customer port. */
#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set or retrieve the current double tagging mode for a port.
 *
 *\description Configuring double tagging requires the caller configure the TPID
 *          inserted using =opennsl_port_tpid_set .
 *          Depending on the underlying device, double tagging may be enabled
 *          on a per port basis or only on a system wide basis. If a specific
 *          port is requested and double tagging is only supported on a device
 *          basis, then this call will affect all ports.
 *          Valid values for double tagging mode are defined in table.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    mode [IN]   Double tag mode as defined in table
 *          =OPENNSL_PORT_DTAG_MODE_table
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Requested double tagging mode is not support on the
 *          device.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the current operating
 *          mode, the value of the parameter mode is undefined.
 ******************************************************************************/
extern int opennsl_port_dtag_mode_set(
    int unit, 
    opennsl_port_t port, 
    int mode) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve the current double tagging mode for a port.
 *
 *\description Configuring double tagging requires the caller configure the TPID
 *          inserted using =opennsl_port_tpid_set .
 *          Depending on the underlying device, double tagging may be enabled
 *          on a per port basis or only on a system wide basis. If a specific
 *          port is requested and double tagging is only supported on a device
 *          basis, then this call will affect all ports.
 *          Valid values for double tagging mode are defined in table.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    mode [OUT]   Double tag mode as defined in table
 *          =OPENNSL_PORT_DTAG_MODE_table
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully
 *\retval    OPENNSL_E_UNAVAIL Requested double tagging mode is not support on the
 *          device.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving the current operating
 *          mode, the value of the parameter mode is undefined.
 ******************************************************************************/
extern int opennsl_port_dtag_mode_get(
    int unit, 
    opennsl_port_t port, 
    int *mode) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_ATTR_ENABLE_MASK       0x00000001 
#define OPENNSL_PORT_ATTR_AUTONEG_MASK      0x00000004 
#define OPENNSL_PORT_ATTR_SPEED_MASK        0x00000008 
#define OPENNSL_PORT_ATTR_DUPLEX_MASK       0x00000010 
#define OPENNSL_PORT_ATTR_LINKSCAN_MASK     0x00000020 
#define OPENNSL_PORT_ATTR_PAUSE_TX_MASK     0x00010000 
#define OPENNSL_PORT_ATTR_PAUSE_RX_MASK     0x00020000 
#define OPENNSL_PORT_ATTR_LOCAL_ADVERT_MASK 0x00080000 
#define OPENNSL_PORT_ATTR_FRAME_MAX_MASK    0x08000000 
#define OPENNSL_PORT_ATTR2_PORT_ABILITY     0x00000001 
#define OPENNSL_PORT_ATTR_ALL_MASK  0xffffffff 
/** opennsl_port_info_s */
typedef struct opennsl_port_info_s {
    uint32 action_mask;                 /**< OPENNSL_PORT_ATTR_xxx. */
    uint32 action_mask2;                /**< OPENNSL_PORT_ATTR2_xxx. */
    int enable;                         
    int linkstatus;                     
    int autoneg;                        
    int speed;                          
    int duplex;                         
    int linkscan;                       
    uint32 learn;                       
    int discard;                        
    uint32 vlanfilter;                  
    int untagged_priority;              
    opennsl_vlan_t untagged_vlan;       
    int stp_state;                      
    int pfm;                            
    int loopback;                       
    int phy_master;                     
    opennsl_port_if_t interface;        
    int pause_tx;                       
    int pause_rx;                       
    int encap_mode;                     
    opennsl_mac_t pause_mac;            
    opennsl_port_abil_t local_advert;   
    opennsl_port_ability_t local_ability; 
    int remote_advert_valid;            
    opennsl_port_abil_t remote_advert;  
    opennsl_port_ability_t remote_ability; 
    int mcast_limit;                    
    int mcast_limit_enable;             
    int bcast_limit;                    
    int bcast_limit_enable;             
    int dlfbc_limit;                    
    int dlfbc_limit_enable;             
    int speed_max;                      
    opennsl_port_abil_t ability;        
    opennsl_port_ability_t port_ability; 
    int frame_max;                      
    opennsl_port_mdix_t mdix;           
    opennsl_port_mdix_status_t mdix_status; 
    opennsl_port_medium_t medium;       
    uint32 fault;                       
} opennsl_port_info_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set multiple port characteristics.
 *
 *\description opennsl_port_info_get and opennsl_port_info_set get and set all
 *          valid settings for the specific device and port in question. For
 *          these calls the action_mask field of the opennsl_port_info_t
 *          structure is ignored on entry, but defined to contain the valid
 *          action mask bits on return.
 *          For all set operations, if both auto-negotiation is enabled and
 *          the speed or duplex are forced to a specific setting, the result
 *          is undefined.
 *          opennsl_port_selective_get and opennsl_port_selective_set operate
 *          similar to opennsl_port_info_get and opennsl_port_info_set with
 *          the exception that action_mask is used to determine which
 *          attributes to set or retrieve.
 *          opennsl_port_info_save and opennsl_port_info_restore provide a
 *          mechanism to save all valid port state and restore it later. The
 *          info parameter to opennsl_port_info_save must be passed unaltered
 *          to opennsl_port_info_restore to restore the previous port state.
 *          Any changes to the info structure results in undefined behavior.
 *          In the case of setting or restoring port configuration, if the API
 *          call returns an error the port state is undefined. Other than as
 *          is required for proper functionality, the order is which the
 *          configuration options are applied is undefined.
 *          Similarly when retrieving options, if an error is returned the
 *          entire contents of the info structure are undefined.
 *          For example, all three implementations of the function
 *          sample_port_speed_get below perform the same function.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    info [IN,OUT]   Pointer to port information structure (see
 *          =PORT_INFORMATION_CONTROL).
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving information the contents
 *          of info are undefined. If setting configuration, the state of the port
 *          is undefined.
 ******************************************************************************/
extern int opennsl_port_selective_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_info_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set multiple port characteristics.
 *
 *\description opennsl_port_info_get and opennsl_port_info_set get and set all
 *          valid settings for the specific device and port in question. For
 *          these calls the action_mask field of the opennsl_port_info_t
 *          structure is ignored on entry, but defined to contain the valid
 *          action mask bits on return.
 *          For all set operations, if both auto-negotiation is enabled and
 *          the speed or duplex are forced to a specific setting, the result
 *          is undefined.
 *          opennsl_port_selective_get and opennsl_port_selective_set operate
 *          similar to opennsl_port_info_get and opennsl_port_info_set with
 *          the exception that action_mask is used to determine which
 *          attributes to set or retrieve.
 *          opennsl_port_info_save and opennsl_port_info_restore provide a
 *          mechanism to save all valid port state and restore it later. The
 *          info parameter to opennsl_port_info_save must be passed unaltered
 *          to opennsl_port_info_restore to restore the previous port state.
 *          Any changes to the info structure results in undefined behavior.
 *          In the case of setting or restoring port configuration, if the API
 *          call returns an error the port state is undefined. Other than as
 *          is required for proper functionality, the order is which the
 *          configuration options are applied is undefined.
 *          Similarly when retrieving options, if an error is returned the
 *          entire contents of the info structure are undefined.
 *          For example, all three implementations of the function
 *          sample_port_speed_get below perform the same function.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    info [IN]   Pointer to port information structure (see
 *          =PORT_INFORMATION_CONTROL).
 *
 *\retval    OPENNSL_E_NONE Operation completed successfully.
 *\retval    OPENNSL_E_XXX Operation failed, if retrieving information the contents
 *          of info are undefined. If setting configuration, the state of the port
 *          is undefined.
 ******************************************************************************/
extern int opennsl_port_selective_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_info_t *info) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set or retrieve color assignment for a given port and priority.
 *
 *\description Assign or examine the color with which packets are marked when
 *          they arrive on the given port with the specified priority in the
 *          VLAN control index.
 *          The network switch family of switches assign the color to
 *          configure the drop precedence (DP) value.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    prio [IN]   VLAN priority (aka 802.1p CoS)
 *\param    color [IN]   One of the OPENNSL color selections: opennslColorGreen,
 *          opennslColorYellow, opennslColorRed, opennslColorDropFirst,
 *          opennslColorPreserve
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_priority_color_set(
    int unit, 
    opennsl_port_t port, 
    int prio, 
    opennsl_color_t color) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or retrieve color assignment for a given port and priority.
 *
 *\description Assign or examine the color with which packets are marked when
 *          they arrive on the given port with the specified priority in the
 *          VLAN control index.
 *          The network switch family of switches assign the color to
 *          configure the drop precedence (DP) value.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    prio [IN]   VLAN priority (aka 802.1p CoS)
 *\param    color [OUT]   One of the OPENNSL color selections: opennslColorGreen,
 *          opennslColorYellow, opennslColorRed, opennslColorDropFirst,
 *          opennslColorPreserve
 *
 *\retval    OPENNSL_E_UNAVAIL Not supported.
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_priority_color_get(
    int unit, 
    opennsl_port_t port, 
    int prio, 
    opennsl_color_t *color) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** opennsl_port_class_e */
typedef enum opennsl_port_class_e {
    opennslPortClassFieldLookup = 0,    /**< Class for field stage Lookup */
    opennslPortClassFieldIngress = 1,   /**< Class for field stage Ingress */
    opennslPortClassFieldEgress = 2,    /**< Class for field stage Egress */
    opennslPortClassFieldIngressPacketProcessing = 6, /**< Packet processing port Class for
                                           field stage Ingress */
    opennslPortClassFieldEgressPacketProcessing = 7, /**< Packet processing port Class for
                                           field stage Egress */
    opennslPortClassEgress = 14,        /**< EGR_PORT class ID field for field
                                           stage Egress */
} opennsl_port_class_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set or get port classification ID to aggregate a group of ports for
 *       further processing such as VLAN translation and field processing.
 *
 *\description Set or get port classification ID to aggregate a group of ports
 *          for further processing such as VLAN translation and field
 *          processing.
 *          The class types are shown in opennsl_port_class_t:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pclass [IN]
 *\param    class_id [IN]   (for _set) Device Class ID.
 *
 *\retval    OPENNSL_E_NONE No Error
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_PORT Invalid Port number specified
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_class_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_class_t pclass, 
    uint32 class_id) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set or get port classification ID to aggregate a group of ports for
 *       further processing such as VLAN translation and field processing.
 *
 *\description Set or get port classification ID to aggregate a group of ports
 *          for further processing such as VLAN translation and field
 *          processing.
 *          The class types are shown in opennsl_port_class_t:.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    pclass [IN]
 *\param    class_id [OUT]   (for _set) Device Class ID.
 *
 *\retval    OPENNSL_E_NONE No Error
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_PORT Invalid Port number specified
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_class_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_class_t pclass, 
    uint32 *class_id) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** Features that can be controlled on a per-port basis. */
typedef enum opennsl_port_control_e {
    opennslPortControlIP4 = 8,          /**< Enable IPv4 Routing on port. */
    opennslPortControlIP6 = 9,          /**< Enable IPv6 Routing on port. */
    opennslPortControlTrustIncomingVlan = 22, /**< Trust incoming packet's Vlan tag */
    opennslPortControlDoNotCheckVlan = 23, /**< Enable/disable spanning tree and Vlan
                                           membership checks on ingress ethernet
                                           and higig packets. For cpu port
                                           configuration is applied only for
                                           higig packets. To configure these
                                           settings for ethernet packets
                                           opennslPortControlDoNotCheckVlanFromCpu
                                           port control can be used. */
    opennslPortControlEgressVlanPriUsesPktPri = 43, /**< If set, outgoing packets derive their
                                           priority from the incoming priority */
    opennslPortControlLanes = 55,       /**< Sets the number of active lanes for a
                                           port that can be dynamically
                                           hot-swapped. */
    opennslPortControlPFCReceive = 59,  /**< Priority Flow Control packet receive
                                           enable */
    opennslPortControlPFCTransmit = 60, /**< Priority Flow Control packet transmit
                                           enable */
    opennslPortControlPFCClasses = 61,  /**< Priority Flow Control number of
                                           classes */
    opennslPortControlPFCPassFrames = 62, /**< Allow Priority Flow Control packets
                                           into switch device */
    opennslPortControlL2Move = 70,      /**< Configure L2 station movement
                                           behavior using OPENNSL_PORT_LEARN_xxx
                                           flags */
    opennslPortControlStatOversize = 92, /**< Threshold above which packet will be
                                           counted as oversized */
    opennslPortControlVxlanEnable = 187, /**< Set per port enable for VXLAN
                                           (Value=TRUE/FALSE) */
    opennslPortControlVxlanTunnelbasedVnId = 188, /**< Set per port VNID lookup key
                                           (Value=TRUE/FALSE) */
    opennslPortControlVxlanDefaultTunnelEnable = 189, /**< Set per port dafult-SVP for Tunnel
                                           lookup failure(Value=TRUE/FALSE) */
    opennslPortControlMmuDrain = 285,   /**< Draining the cells of the port */
    opennslPortControlMmuTrafficEnable = 286, /**< Enable/disable enqueing the packets
                                           to the port */
    opennslPortControlSampleIngressDest = 304, /**< Set Ingress sFlow sample destination */
    opennslPortControlSampleFlexDest = 305, /**< Set Flex sFlow sample destination */
    opennslPortControlSampleFlexRate = 306, /**< Set Flex sFlow sampling rate */
} opennsl_port_control_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get or set various features at the port level.
 *
 *\description Control or examine various features at the port level.
 *          opennsl_port_control_set can be used to enable/disable various
 *          features at the port level. The <type> parameter to the API
 *          identifies the feature to be controlled.
 *          opennsl_port_control_get returns the current value of the port
 *          feature identified by <type> parameter.
 *          The feature types are show in =PORT_CONTROL_v :.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Port feature enumerator
 *\param    value [IN]   Value of the bit field in port table
 *
 *\retval    OPENNSL_E_NONE No Error
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_PORT Invalid Port number specified
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_control_set(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_control_t type, 
    int value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get or set various features at the port level.
 *
 *\description Control or examine various features at the port level.
 *          opennsl_port_control_set can be used to enable/disable various
 *          features at the port level. The <type> parameter to the API
 *          identifies the feature to be controlled.
 *          opennsl_port_control_get returns the current value of the port
 *          feature identified by <type> parameter.
 *          The feature types are show in =PORT_CONTROL_v :.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Device or logical port number
 *\param    type [IN]   Port feature enumerator
 *\param    value [OUT]   Value of the bit field in port table
 *
 *\retval    OPENNSL_E_NONE No Error
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_PORT Invalid Port number specified
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_control_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_port_control_t type, 
    int *value) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get the list of ancilliary/flex ports belonging to the same port block
 *       as the controlling port.
 *
 *\description Given a controlling port, this API returns the set of
 *          ancilliary/flex ports  belonging to the group (port block) that
 *          can be created by performing  Flex-IO operation on the controlling
 *          port using API opennsl_port_control_set(unit,  port,
 *          opennslPortControlLanes, lanes). If the input port is not a
 *          controlling port,  OPENNSL_E_PORT error will be returned.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Controlling port
 *\param    pbmp [OUT]   List of subsidiary ports in the same block as the
 *          controlling port
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_subsidiary_ports_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_pbmp_t *pbmp) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initializes the opennsl_port_info_t structure.
 *
 *\description Initializes the opennsl_port_info_t structure.
 *
 *\param    info [IN,OUT]   Pointer to port information structure (see
 *          =PORT_INFORMATION_CONTROL).
 *
 *\returns  Nothing
 ******************************************************************************/
extern void opennsl_port_info_t_init(
    opennsl_port_info_t *info) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize a Port Ability structure.
 *
 *\description Initializes a port abilities structure to default values. This
 *          function should be used to initialize any Port Ability structure
 *          prior to filling it out and passing it to an API function. This
 *          ensures that subsequent API releases may add new structure members
 *          to the opennsl_port_ability_t structure, and
 *          opennsl_port_ability_t_init will initialize the new members to
 *          correct default values.
 *
 *\param    ability [IN,OUT]
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_port_ability_t_init(
    opennsl_port_ability_t *ability) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Initialize a Port Configuration structure.
 *
 *\description Initializes a port configuration structure to default values. This
 *          function should be used to initialize any Port Configuration
 *          structure prior to filling it out and passing it to an API
 *          function. This ensures that subsequent API releases may add new
 *          structure members to the opennsl_port_config_t structure, and
 *          opennsl_port_config_t_init will initialize the new members to
 *          correct default values.
 *
 *\param    pconfig [IN,OUT]   Pointer to Port Configuration structure to
 *          initialize.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_port_config_t_init(
    opennsl_port_config_t *pconfig) LIB_DLL_EXPORTED ;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Get the GPORT ID for the specified local port number.
 *
 *\description This API can be used to get the GPORT ID corresponding to a local
 *          port number.  The supplied port number should return FALSE on a
 *          OPENNSL_GPORT_IS_SET(port) test.
 *          The GPORT ID returned in this API is a MODPORT type. Therefore
 *          this call will fail on devices without a module ID.
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   Port number
 *\param    gport [OUT]   GPORT ID
 *
 *\retval    OPENNSL_E_NONE No Error
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_PORT Invalid Port number
 *\retval    OPENNSL_E_PARAM Invalid Parameter
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_gport_get(
    int unit, 
    opennsl_port_t port, 
    opennsl_gport_t *gport) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Get local port number encoded within a GPORT ID.
 *
 *\description This API can be used to get a local port number encoded into a
 *          GPORT ID. This resulting port number will return FALSE on a
 *          OPENNSL_GPORT_IS_SET(port) test.  To encode the result as a local
 *          port gport ID, use OPENNSL_GPORT_LOCAL_SET(gport_local,
 *          local_port);
 *          If the encoding of GPORT ID does not contain a local port on a
 *          device, this API will return an error. GPORT ID may be encoded as
 *          both MODPORT and DEVPORT.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   GPORT ID
 *\param    local_port [OUT]   Local port number
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_local_get(
    int unit, 
    opennsl_gport_t gport, 
    opennsl_port_t *local_port) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Enable/disable packet and byte counters for the selected gport.
 *
 *\description This API will initialize statistic collection for the given GPORT
 *          (enable=TRUE) or release the HW resources used for the tracking
 *          the statistics (enable=FALSE).
 *
 *\param    unit [IN]   Unit number.
 *\param    port [IN]   GPORT ID
 *\param    enable [IN]   Non-zero to enable counter collection, zero to disable.
 *
 *\retval    OPENNSL_E_XXX
 ******************************************************************************/
extern int opennsl_port_stat_enable_set(
    int unit, 
    opennsl_gport_t port, 
    int enable) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

#define OPENNSL_PORT_CONTROL_SAMPLE_DEST_CPU 0x1        /**< Copy packet samples to
                                                          CPU */
#define OPENNSL_PORT_CONTROL_SAMPLE_DEST_MIRROR 0x2        /**< Copy packet samples to
                                                          all mirror
                                                          destinations created
                                                          with
                                                          OPENNSL_MIRROR_PORT_SFLOW
                                                          flag */
/** Parameter for opennslPortControlFieldEgressClassSelect */
typedef enum opennsl_port_field_egress_class_select_e {
    opennslPortEgressClassSelectPort = 1, /**< Class Id from Port Interface. */
} opennsl_port_field_egress_class_select_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Assign/retrieve the Priority Group mapped to the input priority.
 *
 *\description Assign/retrieve the Priority Group mapped to the input priority.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   generic port
 *\param    prio [IN]   input priority
 *\param    priority_group  [IN]   priority group ID that the input priority
 *          mapped to
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_priority_group_mapping_set(
    int unit, 
    opennsl_gport_t gport, 
    int prio, 
    int priority_group ) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Assign/retrieve the Priority Group mapped to the input priority.
 *
 *\description Assign/retrieve the Priority Group mapped to the input priority.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   generic port
 *\param    prio [IN]   input priority
 *\param    priority_group [OUT]   priority group ID that the input priority
 *          mapped to
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_priority_group_mapping_get(
    int unit, 
    opennsl_gport_t gport, 
    int prio, 
    int *priority_group) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/** Priority Group attributes */
typedef struct opennsl_port_priority_group_config_s {
    int pfc_transmit_enable;    /**< enable/disable of transmitting PFC message
                                   even in IBP state */
} opennsl_port_priority_group_config_t;

#ifndef OPENNSL_HIDE_DISPATCHABLE

/***************************************************************************//** 
 *\brief Set/get the port priority group configuration.
 *
 *\description Set/get the port Priority Group configuration.
 *          The structure opennsl_port_priority_group_config_t is used to
 *          describte the attributes of a Priority Group.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   generic port
 *\param    priority_group [IN]   priority group id
 *\param    prigrp_config [IN]   structure describes port priority group
 *          configuration
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_priority_group_config_set(
    int unit, 
    opennsl_gport_t gport, 
    int priority_group, 
    opennsl_port_priority_group_config_t *prigrp_config) LIB_DLL_EXPORTED ;

/***************************************************************************//** 
 *\brief Set/get the port priority group configuration.
 *
 *\description Set/get the port Priority Group configuration.
 *          The structure opennsl_port_priority_group_config_t is used to
 *          describte the attributes of a Priority Group.
 *
 *\param    unit [IN]   Unit number.
 *\param    gport [IN]   generic port
 *\param    priority_group [IN]   priority group id
 *\param    prigrp_config [OUT]   structure describes port priority group
 *          configuration
 *
 *\retval    OPENNSL_E_NONE Success
 *\retval    OPENNSL_E_UNAVAIL Feature unavailable
 *\retval    OPENNSL_E_XXX Error occurred
 ******************************************************************************/
extern int opennsl_port_priority_group_config_get(
    int unit, 
    opennsl_gport_t gport, 
    int priority_group, 
    opennsl_port_priority_group_config_t *prigrp_config) LIB_DLL_EXPORTED ;

#endif /* OPENNSL_HIDE_DISPATCHABLE */

/***************************************************************************//** 
 *\brief Initialize a port priority group configuration struct.
 *
 *\description Initializes a Priority Group configuration structure to default
 *          values. This function should be used to initialize any Priority
 *          Group configuration structure prior to filling it out and passing
 *          it to an API function.
 *
 *\param    prigrp_config [IN,OUT]   Pointer to the priority group configuration
 *          object struct.
 *
 *\retval    None.
 ******************************************************************************/
extern void opennsl_port_priority_group_config_t_init(
    opennsl_port_priority_group_config_t *prigrp_config) LIB_DLL_EXPORTED ;

#include <opennsl/portX.h>
#endif /* __OPENNSL_PORT_H__ */
/*@}*/
