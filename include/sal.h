#pragma once

#ifndef _SAL_DISABLE_H
#define _SAL_DISABLE_H 1

/*
 * This header disables MSVC's SAL annotation
 * feature by redefining them to nothing,
 * because it messes stuff up otherwise
 */

#ifdef _SAL_VERSION
#undef _In_
#undef _Out_
#undef _Inout_

#undef _In_z_
#undef _Inout_z_

#undef _In_reads_
#undef _In_reads_bytes_
#undef _In_reads_z_
#undef _In_reads_or_z_

#undef _Out_writes_
#undef _Out_writes_bytes_
#undef _Out_writes_
#undef _Out_writes_z_

#undef _Inout_updates_
#undef _Inout_updates_bytes_
#undef _Inout_updates_z

#undef _Out_writes_to_
#undef _Out_writes_bytes_to_
#undef _Out_writes_all_
#undef _Out_writes_bytes_all_

#undef _Inout_updates_to_
#undef _Inout_updates_bytes_to_
#undef _Inout_updates_all_
#undef _Inout_updates_bytes_all_
#undef _Inout_updates_to_

#undef _In_reads_to_ptr_
#undef _In_reads_to_ptr_z_

#undef _Out_writes_to_ptr_
#undef _Out_writes_to_ptr_z_

#undef _In_opt_
#undef _Out_opt_
#undef _Inout_opt_

#undef _In_opt_z_
#undef _Inout_opt_z_

#undef _In_reads_opt_
#undef _In_reads_bytes_opt_
#undef _In_reads_opt_z_
#undef _In_reads_or_opt_z_

#undef _Out_writes_opt_
#undef _Out_writes_bytes_opt_
#undef _Out_writes_opt_
#undef _Out_writes_opt_z_

#undef _Inout_updates_opt_
#undef _Inout_updates_bytes_opt_
#undef _Inout_updates_opt_z_

#undef _Out_writes_to_opt_
#undef _Out_writes_bytes_to_opt_
#undef _Out_writes_all_opt_
#undef _Out_writes_bytes_all_opt_

#undef _Inout_updates_to_opt_
#undef _Inout_updates_bytes_to_opt_
#undef _Inout_updates_all_opt_
#undef _Inout_updates_bytes_all_opt_
#undef _Inout_updates_to_opt_

#undef _In_reads_to_ptr_opt_
#undef _In_reads_to_ptr_opt_z_

#undef _Out_writes_to_ptr_opt_
#undef _Out_writes_to_ptr_opt_z_

#undef _Outptr_
#undef _Outptr_opt_

#undef _Outptr_result_maybenull_
#undef _Outptr_opt_result_maybenull_

#undef _Outptr_result_z_
#undef _Outptr_opt_result_z_

#undef _Outptr_result_maybenull_z_
#undef _Outptr_opt_result_maybenull_z_

#undef _COM_Outptr_
#undef _COM_Outptr_opt_

#undef _COM_Outptr_result_maybenull_
#undef _COM_Outptr_opt_result_maybenull_

#undef _Outptr_result_buffer_
#undef _Outptr_result_bytebuffer_

#undef _Outptr_opt_result_buffer_
#undef _Outptr_opt_result_bytebuffer_

#undef _Outptr_result_buffer_to_
#undef _Outptr_result_bytebuffer_to_

#undef _Outptr_opt_result_buffer_to_
#undef _Outptr_opt_result_bytebuffer_to_

#undef _Result_nullonfailure_
#undef _Result_zeroonfailure_

#undef _Outptr_result_nullonfailure_

#undef _Outptr_opt_result_nullonfailure_

#undef _Outref_result_nullonfailure_
#endif /* _SAL_VERSION */

#endif /* !_SAL_DISABLE_H */
