
/*
 * Copyright (C) 2006 Movilgate SRL.
 * File  : submit_sm_test.c
 * Author: Raul Tremsal <rtremsal@movilgate.com>
 *
 * This file is part of libsmpp34 (c-open-smpp3.4 library).
 *
 * The libsmpp34 library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation; either version 2.1 of the 
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public 
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this library; if not, write to the Free Software Foundation, 
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

#ifdef __linux__
#include <stdint.h>
#endif

#include "smpp34.h"
#include "smpp34_structs.h"
#include "smpp34_params.h"
#include "core.h"

#define TEXTO "Raul Antonio Tremsal"

int
main( int argc, char *argv[] )
{

    submit_sm_t a;
    submit_sm_t b;
    tlv_t tlv;

    memset(&a, 0, sizeof(submit_sm_t));
    memset(&b, 0, sizeof(submit_sm_t));
    memset(&tlv, 0, sizeof(tlv_t));

    /* Init PDU ***********************************************************/
    b.command_length   = 0;
    b.command_id       = SUBMIT_SM;
    b.command_status   = ESME_ROK;
    b.sequence_number  = 1;
    snprintf(b.service_type, sizeof(b.service_type), "%s", "SMS");
    b.source_addr_ton  = 2;
    b.source_addr_npi  = 1;
    snprintf(b.source_addr, sizeof(b.source_addr), "%s", 
                                                   "09000011111");
    b.dest_addr_ton    = 2;
    b.dest_addr_npi    = 0;
    snprintf(b.destination_addr, sizeof(b.destination_addr), "%s", 
                                                 "1121312309000");
    b.esm_class        = 0;
    b.protocol_id      = 0;
    b.priority_flag    = 0;
    snprintf( b.schedule_delivery_time, TIME_LENGTH, "%s", "");
    snprintf( b.validity_period, TIME_LENGTH, "%s", "");
    b.registered_delivery = 0;
    b.replace_if_present_flag =0;
    b.data_coding         = 0;
    b.sm_default_msg_id   = 0;
    b.sm_length           = strlen(TEXTO);
    memcpy(b.short_message, TEXTO, b.sm_length);

    tlv.tag = TLVID_user_message_reference;
    tlv.length = sizeof(uint16_t);
    tlv.value.val16 = 0x0024;
    build_tlv( &(b.tlv), &tlv );

    tlv.tag = TLVID_message_payload;
    tlv.length = strlen(TEXTO);
    memcpy(tlv.value.octet, TEXTO, tlv.length);
    build_tlv( &(b.tlv), &tlv );

    doTest(SUBMIT_SM, &a, &b);
    destroy_tlv( b.tlv );
    destroy_tlv( a.tlv );
    return( 0 );
};
