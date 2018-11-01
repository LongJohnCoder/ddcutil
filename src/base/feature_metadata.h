/* @file feature_metadata.h
 *
 * Functions for external and internal representation of
 * display-specific feature metadata.
 */

// Copyright (C) 2018 Sanford Rockowitz <rockowitz@minsoft.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#ifndef FEATURE_METADATA_H_
#define FEATURE_METADATA_H_

#include <stdbool.h>

#include "ddcutil_types.h"

#include "util/data_structures.h"


// Simple stripped-down version of Parsed_Nontable_Vcp_Response
typedef
struct {
   DDCA_Vcp_Feature_Code   vcp_code;
   ushort max_value;
   ushort cur_value;
   // for new way
   Byte   mh;
   Byte   ml;
   Byte   sh;
   Byte   sl;
} Nontable_Vcp_Value;


// Prototypes for functions that format feature values

typedef
bool (*Format_Normal_Feature_Detail_Function) (
          Nontable_Vcp_Value*     code_info,
          DDCA_MCCS_Version_Spec  vcp_version,
          char *                  buffer,
          int                     bufsz);

typedef
bool (*Format_Normal_Feature_Detail_Function2) (
          Nontable_Vcp_Value*        code_info,
       // Display_Ref *              dref,
       // DDCA_MCCS_Version_Spec     vcp_version,
          DDCA_Feature_Value_Entry * sl_values,
          char *                     buffer,
          int                        bufsz);

typedef
bool (*Format_Table_Feature_Detail_Function) (
          Buffer *                data_bytes,
          DDCA_MCCS_Version_Spec  vcp_version,
          char **                 p_result_buffer);


// combines Format_Normal_Feature_Detail_Fucntion, Format_Normal_Detail_Function2
typedef
bool (*Format_Normal_Feature_Detail_Function3) (
          Nontable_Vcp_Value*        code_info,
          DDCA_MCCS_Version_Spec     vcp_version,
          DDCA_Feature_Value_Entry * sl_values,
          char *                     buffer,
          int                        bufsz);

//typedef
//bool (*Format_Table_Feature_Detail_Functionx) (
//          Buffer *                data_bytes,
//          DDCA_MCCS_Version_Spec  vcp_version,
//          char **                 p_result_buffer);


// Feature value table functions

void   dbgrpt_sl_value_table(DDCA_Feature_Value_Entry * table, int depth);
DDCA_Feature_Value_Entry *
       copy_sl_value_table(DDCA_Feature_Value_Entry * oldtable);
void   free_sl_value_table(DDCA_Feature_Value_Entry * table);

// Feature Flags

char * interpret_feature_flags(DDCA_Version_Feature_Flags flags);


// DDCA_Feature_Metadata

void dbgrpt_ddca_feature_metadata(DDCA_Feature_Metadata * md, int depth);


// Display_Feature_Metadata

// merges DDCA_Version_Feature_Info, DDCA_Feature_Metadata, Internal_Feature_Metadata

/** Display specific feature description */

#define DISPLAY_FEATURE_METADATA_MARKER "DFMD"
typedef
struct {
   char                                    marker[4];
   DDCA_Display_Ref                        display_ref;    // needed?
   DDCA_Vcp_Feature_Code                   feature_code;
   DDCA_MCCS_Version_Spec                  vcp_version;    // needed ?
   char *                                  feature_name;
   char *                                  feature_desc;
   DDCA_Feature_Value_Entry *              sl_values;     /**< valid when DDCA_SIMPLE_NC set */
   DDCA_Feature_Flags                      feature_flags;
   Format_Normal_Feature_Detail_Function   nontable_formatter;
   Format_Normal_Feature_Detail_Function2  nontable_formatter_sl;
   Format_Normal_Feature_Detail_Function3  nontable_formatter_universal;   // the future
   Format_Table_Feature_Detail_Function    table_formatter;
} Display_Feature_Metadata;


void dbgrpt_display_feature_metadata(
      Display_Feature_Metadata * meta,
      int                        depth);

void dfm_free(
      Display_Feature_Metadata * meta);

Display_Feature_Metadata *
      dfm_new(DDCA_Vcp_Feature_Code feature_code);

void  dfm_set_feature_name(Display_Feature_Metadata * meta, const char * feature_name);
void  dfm_set_feature_desc(Display_Feature_Metadata * meta, const char * feature_desc);

// Conversion functions

DDCA_Feature_Metadata *
      dfm_to_ddca_feature_metadata(Display_Feature_Metadata * dfm);

Display_Feature_Metadata *
      dfm_from_ddca_feature_metadata(DDCA_Feature_Metadata * meta);


#endif /* FEATURE_METADATA_H_ */
