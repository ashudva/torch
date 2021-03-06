#ifndef __LANTERN_H__
#define __LANTERN_H__

#ifndef _WIN32
#include <dlfcn.h>
#else
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

#ifndef HOST_API
#define HOST_API inline
#endif

#ifdef LANTERN_BUILD
#define LANTERN_PTR
#define LANTERN_HEADERS_ONLY

#ifdef _WIN32
#define LANTERN_API extern "C" __declspec(dllexport)
#endif
#else
#define LANTERN_PTR *
#endif

#ifndef LANTERN_API
#ifdef LANTERN_HEADERS_ONLY
#define LANTERN_API extern
#else
#define LANTERN_API
#endif
#endif

#ifndef LANTERN_HOST_HANDLER
#define LANTERN_HOST_HANDLER
#endif

#include <stdint.h>
#include <stdio.h>

extern int lanternLogEnabled;
#define LLOG(...) if ((lanternLogEnabled & 1) == 1) {              \
  printf("%ld INFO ", time(NULL));                                 \
  printf(__VA_ARGS__);                                             \
  printf("\n");                                                    \
}                                                                  \
if ((lanternLogEnabled & 2) == 2) {                                \
  FILE *pFile = fopen("lantern.log", "a");                         \
  fprintf(pFile, "%ld INFO ", time(NULL));                         \
  fprintf(pFile, __VA_ARGS__);                                     \
  fprintf(pFile, "\n");                                            \
  fclose(pFile);                                                   \
}

#ifdef LANTERN_BUILD
extern std::string *pLanternLastError;
#endif
#define LANTERN_FUNCTION_START                                     \
  LLOG("Entering %s", __func__)                                    \
  try {
#define LANTERN_FUNCTION_END_RET(ret)                              \
} catch(const std::exception& ex) {                                \
  LLOG("Error %s in %s", ex.what(), __func__)                      \
  pLanternLastError = new std::string(ex.what());                  \
  return ret;                                                      \
} catch(std::string& ex) {                                         \
  LLOG("Error %s in %s", ex.c_str(), __func__)                     \
  pLanternLastError = new std::string(ex);                         \
  return ret;                                                      \
} catch(...) {                                                     \
  LLOG("Error in %s", __func__)                                    \
  pLanternLastError = new std::string("Unknown error. ");          \
  return ret;                                                      \
}
#define LANTERN_FUNCTION_END LANTERN_FUNCTION_END_RET(NULL)
#define LANTERN_FUNCTION_END_VOID                                  \
} catch(const std::exception& ex) {                                \
  LLOG("Error %s in %s", ex.what(), __func__)                      \
  pLanternLastError = new std::string(ex.what());                  \
} catch(std::string& ex) {                                         \
  LLOG("Error %s in %s", ex.c_str(), __func__)                     \
  pLanternLastError = new std::string(ex);                         \
} catch(...) {                                                     \
  LLOG("Error in %s", __func__)                                    \
  pLanternLastError = new std::string("Unknown error. ");          \
}

#ifdef __cplusplus
extern "C"
{
#endif

  LANTERN_API void(LANTERN_PTR lanternConfigure)(int log);
  LANTERN_API const char*(LANTERN_PTR lanternVersion)();
  LANTERN_API void(LANTERN_PTR lanternSetLastError)(const char*);
  LANTERN_API void(LANTERN_PTR lanternLastErrorClear)();
  LANTERN_API const char*(LANTERN_PTR lanternLastError)();
  LANTERN_API void(LANTERN_PTR lanternTest)();
  LANTERN_API void *(LANTERN_PTR _lantern_Device)(const char *type, int64_t index, bool useIndex);
  HOST_API void * lantern_Device(const char *type, int64_t index, bool useIndex) { void * ret = _lantern_Device(type, index, useIndex); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Device_type)(void *device);
  HOST_API const char * lantern_Device_type(void *device) { const char * ret = _lantern_Device_type(device); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Device_index)(void *device);
  HOST_API int64_t lantern_Device_index(void *device) { int64_t ret = _lantern_Device_index(device); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_from_blob)(void *data, int64_t *sizes, size_t sizes_size, void *options);
  HOST_API void * lantern_from_blob(void *data, int64_t *sizes, size_t sizes_size, void *options) { void * ret = _lantern_from_blob(data, sizes, sizes_size, options); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Tensor_StreamInsertion)(void *x);
  HOST_API const char * lantern_Tensor_StreamInsertion(void *x) { const char * ret = _lantern_Tensor_StreamInsertion(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions)();
  HOST_API void * lantern_TensorOptions() { void * ret = _lantern_TensorOptions(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions_dtype)(void *self, void *dtype);
  HOST_API void * lantern_TensorOptions_dtype(void *self, void *dtype) { void * ret = _lantern_TensorOptions_dtype(self, dtype); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions_layout)(void *self, void *layout);
  HOST_API void * lantern_TensorOptions_layout(void *self, void *layout) { void * ret = _lantern_TensorOptions_layout(self, layout); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions_device)(void *self, void *device);
  HOST_API void * lantern_TensorOptions_device(void *self, void *device) { void * ret = _lantern_TensorOptions_device(self, device); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions_requires_grad)(void *self, bool requires_grad);
  HOST_API void * lantern_TensorOptions_requires_grad(void *self, bool requires_grad) { void * ret = _lantern_TensorOptions_requires_grad(self, requires_grad); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorOptions_pinned_memory)(void *self, bool pinned_memory);
  HOST_API void * lantern_TensorOptions_pinned_memory(void *self, bool pinned_memory) { void * ret = _lantern_TensorOptions_pinned_memory(self, pinned_memory); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_float32)();
  HOST_API void * lantern_Dtype_float32() { void * ret = _lantern_Dtype_float32(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_float64)();
  HOST_API void * lantern_Dtype_float64() { void * ret = _lantern_Dtype_float64(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_float16)();
  HOST_API void * lantern_Dtype_float16() { void * ret = _lantern_Dtype_float16(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_uint8)();
  HOST_API void * lantern_Dtype_uint8() { void * ret = _lantern_Dtype_uint8(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_int8)();
  HOST_API void * lantern_Dtype_int8() { void * ret = _lantern_Dtype_int8(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_int16)();
  HOST_API void * lantern_Dtype_int16() { void * ret = _lantern_Dtype_int16(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_int32)();
  HOST_API void * lantern_Dtype_int32() { void * ret = _lantern_Dtype_int32(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_int64)();
  HOST_API void * lantern_Dtype_int64() { void * ret = _lantern_Dtype_int64(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_bool)();
  HOST_API void * lantern_Dtype_bool() { void * ret = _lantern_Dtype_bool(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Dtype_type)(void *dtype);
  HOST_API const char * lantern_Dtype_type(void *dtype) { const char * ret = _lantern_Dtype_type(dtype); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_vector_int64_t)(int64_t *x, size_t x_size);
  HOST_API void * lantern_vector_int64_t(int64_t *x, size_t x_size) { void * ret = _lantern_vector_int64_t(x, x_size); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_IntArrayRef)(int64_t *x, size_t x_size);
  HOST_API void * lantern_IntArrayRef(int64_t *x, size_t x_size) { void * ret = _lantern_IntArrayRef(x, x_size); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_MemoryFormat_Contiguous)();
  HOST_API void * lantern_MemoryFormat_Contiguous() { void * ret = _lantern_MemoryFormat_Contiguous(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_MemoryFormat_Preserve)();
  HOST_API void * lantern_MemoryFormat_Preserve() { void * ret = _lantern_MemoryFormat_Preserve(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_MemoryFormat_ChannelsLast)();
  HOST_API void * lantern_MemoryFormat_ChannelsLast() { void * ret = _lantern_MemoryFormat_ChannelsLast(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_MemoryFormat_type)(void *format);
  HOST_API const char * lantern_MemoryFormat_type(void *format) { const char * ret = _lantern_MemoryFormat_type(format); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_clone)(void *self);
  HOST_API void * lantern_Tensor_clone(void *self) { void * ret = _lantern_Tensor_clone(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_permute)(void *self, void *dims);
  HOST_API void * lantern_Tensor_permute(void *self, void *dims) { void * ret = _lantern_Tensor_permute(self, dims); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_contiguous)(void *self);
  HOST_API void * lantern_Tensor_contiguous(void *self) { void * ret = _lantern_Tensor_contiguous(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_to)(void *self, void *options);
  HOST_API void * lantern_Tensor_to(void *self, void *options) { void * ret = _lantern_Tensor_to(self, options); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_set_requires_grad)(void *self, bool requires_grad);
  HOST_API void * lantern_Tensor_set_requires_grad(void *self, bool requires_grad) { void * ret = _lantern_Tensor_set_requires_grad(self, requires_grad); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API double *(LANTERN_PTR _lantern_Tensor_data_ptr_double)(void *self);
  HOST_API double * lantern_Tensor_data_ptr_double(void *self) { double * ret = _lantern_Tensor_data_ptr_double(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API uint8_t *(LANTERN_PTR _lantern_Tensor_data_ptr_uint8_t)(void *self);
  HOST_API uint8_t * lantern_Tensor_data_ptr_uint8_t(void *self) { uint8_t * ret = _lantern_Tensor_data_ptr_uint8_t(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int32_t *(LANTERN_PTR _lantern_Tensor_data_ptr_int32_t)(void *self);
  HOST_API int32_t * lantern_Tensor_data_ptr_int32_t(void *self) { int32_t * ret = _lantern_Tensor_data_ptr_int32_t(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int16_t *(LANTERN_PTR _lantern_Tensor_data_ptr_int16_t)(void *self);
  HOST_API int16_t * lantern_Tensor_data_ptr_int16_t(void *self) { int16_t * ret = _lantern_Tensor_data_ptr_int16_t(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool *(LANTERN_PTR _lantern_Tensor_data_ptr_bool)(void *self);
  HOST_API bool * lantern_Tensor_data_ptr_bool(void *self) { bool * ret = _lantern_Tensor_data_ptr_bool(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Tensor_numel)(void *self);
  HOST_API int64_t lantern_Tensor_numel(void *self) { int64_t ret = _lantern_Tensor_numel(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Tensor_size)(void *self, int64_t i);
  HOST_API int64_t lantern_Tensor_size(void *self, int64_t i) { int64_t ret = _lantern_Tensor_size(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Tensor_ndimension)(void *self);
  HOST_API int64_t lantern_Tensor_ndimension(void *self) { int64_t ret = _lantern_Tensor_ndimension(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_dtype)(void *self);
  HOST_API void * lantern_Tensor_dtype(void *self) { void * ret = _lantern_Tensor_dtype(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Generator)();
  HOST_API void * lantern_Generator() { void * ret = _lantern_Generator(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API uint64_t(LANTERN_PTR _lantern_Generator_current_seed)(void *generator);
  HOST_API uint64_t lantern_Generator_current_seed(void *generator) { uint64_t ret = _lantern_Generator_current_seed(generator); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_Generator_set_current_seed)(void *generator, uint64_t seed);
  HOST_API void lantern_Generator_set_current_seed(void *generator, uint64_t seed) { _lantern_Generator_set_current_seed(generator, seed); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_QScheme_per_channel_affine)();
  HOST_API void * lantern_QScheme_per_channel_affine() { void * ret = _lantern_QScheme_per_channel_affine(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_QScheme_per_tensor_affine)();
  HOST_API void * lantern_QScheme_per_tensor_affine() { void * ret = _lantern_QScheme_per_tensor_affine(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_QScheme_per_channel_symmetric)();
  HOST_API void * lantern_QScheme_per_channel_symmetric() { void * ret = _lantern_QScheme_per_channel_symmetric(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_QScheme_per_tensor_symmetric)();
  HOST_API void * lantern_QScheme_per_tensor_symmetric() { void * ret = _lantern_QScheme_per_tensor_symmetric(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_QScheme_type)(void *x);
  HOST_API const char * lantern_QScheme_type(void *x) { const char * ret = _lantern_QScheme_type(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorList)();
  HOST_API void * lantern_TensorList() { void * ret = _lantern_TensorList(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_TensorList_push_back)(void *self, void *x);
  HOST_API void lantern_TensorList_push_back(void *self, void *x) { _lantern_TensorList_push_back(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_TensorList_at)(void *self, int64_t i);
  HOST_API void * lantern_TensorList_at(void *self, int64_t i) { void * ret = _lantern_TensorList_at(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_TensorList_size)(void *self);
  HOST_API int64_t lantern_TensorList_size(void *self) { int64_t ret = _lantern_TensorList_size(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Scalar)(void *value, const char *type);
  HOST_API void * lantern_Scalar(void *value, const char *type) { void * ret = _lantern_Scalar(value, type); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_vector_get)(void *x, int i);
  HOST_API void * lantern_vector_get(void *x, int i) { void * ret = _lantern_vector_get(x, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_int)(int x);
  HOST_API void * lantern_int(int x) { void * ret = _lantern_int(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_int64_t)(int64_t x);
  HOST_API void * lantern_int64_t(int64_t x) { void * ret = _lantern_int64_t(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_bool)(bool x);
  HOST_API void * lantern_bool(bool x) { void * ret = _lantern_bool(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dimname)(const char *name);
  HOST_API void * lantern_Dimname(const char *name) { void * ret = _lantern_Dimname(name); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_DimnameList)();
  HOST_API void * lantern_DimnameList() { void * ret = _lantern_DimnameList(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_DimnameList_push_back)(void *list, void *dimname);
  HOST_API void lantern_DimnameList_push_back(void *list, void *dimname) { _lantern_DimnameList_push_back(list, dimname); LANTERN_HOST_HANDLER }
  LANTERN_API const char *(LANTERN_PTR _lantern_Dimname_to_string)(void *dimname);
  HOST_API const char * lantern_Dimname_to_string(void *dimname) { const char * ret = _lantern_Dimname_to_string(dimname); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_DimnameList_size)(void *list);
  HOST_API int64_t lantern_DimnameList_size(void *list) { int64_t ret = _lantern_DimnameList_size(list); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_DimnameList_at)(void *list, int i);
  HOST_API void * lantern_DimnameList_at(void *list, int i) { void * ret = _lantern_DimnameList_at(list, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Scalar_nullopt)();
  HOST_API void * lantern_Scalar_nullopt() { void * ret = _lantern_Scalar_nullopt(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_Tensor_delete)(void *);
  HOST_API void lantern_Tensor_delete(void * x) { _lantern_Tensor_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_bool_delete)(void *);
  HOST_API void lantern_bool_delete(void * x) { _lantern_bool_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_int64_t_delete)(void *);
  HOST_API void lantern_int64_t_delete(void * x) { _lantern_int64_t_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorList_delete)(void *);
  HOST_API void lantern_TensorList_delete(void * x) { _lantern_TensorList_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_double_delete)(void *);
  HOST_API void lantern_double_delete(void * x) { _lantern_double_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_QScheme_delete)(void *);
  HOST_API void lantern_QScheme_delete(void * x) { _lantern_QScheme_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Scalar_delete)(void *);
  HOST_API void lantern_Scalar_delete(void * x) { _lantern_Scalar_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_ScalarType_delete)(void *);
  HOST_API void lantern_ScalarType_delete(void * x) { _lantern_ScalarType_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorOptions_delete)(void *x);
  HOST_API void lantern_TensorOptions_delete(void *x) { _lantern_TensorOptions_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Dtype_delete)(void *x);
  HOST_API void lantern_Dtype_delete(void *x) { _lantern_Dtype_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Device_delete)(void *x);
  HOST_API void lantern_Device_delete(void *x) { _lantern_Device_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Layout_delete)(void *x);
  HOST_API void lantern_Layout_delete(void *x) { _lantern_Layout_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorOptions_print)(void *self);
  HOST_API void lantern_TensorOptions_print(void *self) { _lantern_TensorOptions_print(self); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorOptions_address)(void *self);
  HOST_API void lantern_TensorOptions_address(void *self) { _lantern_TensorOptions_address(self); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Generator_delete)(void *x);
  HOST_API void lantern_Generator_delete(void *x) { _lantern_Generator_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_Dimname_delete)(void *x);
  HOST_API void lantern_Dimname_delete(void *x) { _lantern_Dimname_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_DimnameList_delete)(void *x);
  HOST_API void lantern_DimnameList_delete(void *x) { _lantern_DimnameList_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_MemoryFormat_delete)(void *x);
  HOST_API void lantern_MemoryFormat_delete(void *x) { _lantern_MemoryFormat_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API int64_t(LANTERN_PTR _lantern_Reduction_Sum)();
  HOST_API int64_t lantern_Reduction_Sum() { int64_t ret = _lantern_Reduction_Sum(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Reduction_None)();
  HOST_API int64_t lantern_Reduction_None() { int64_t ret = _lantern_Reduction_None(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_Reduction_Mean)();
  HOST_API int64_t lantern_Reduction_Mean() { int64_t ret = _lantern_Reduction_Mean(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_double)(double x);
  HOST_API void * lantern_double(double x) { void * ret = _lantern_double(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_quint8)();
  HOST_API void * lantern_Dtype_quint8() { void * ret = _lantern_Dtype_quint8(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_qint8)();
  HOST_API void * lantern_Dtype_qint8() { void * ret = _lantern_Dtype_qint8(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Dtype_qint32)();
  HOST_API void * lantern_Dtype_qint32() { void * ret = _lantern_Dtype_qint32(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_Tensor_is_quantized)(void *x);
  HOST_API bool lantern_Tensor_is_quantized(void *x) { bool ret = _lantern_Tensor_is_quantized(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_autograd_set_grad_mode)(bool enabled);
  HOST_API void lantern_autograd_set_grad_mode(bool enabled) { _lantern_autograd_set_grad_mode(enabled); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_undefined)();
  HOST_API void * lantern_Tensor_undefined() { void * ret = _lantern_Tensor_undefined(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_grad)(void *self);
  HOST_API void * lantern_Tensor_grad(void *self) { void * ret = _lantern_Tensor_grad(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_Tensor_requires_grad)(void *self);
  HOST_API bool lantern_Tensor_requires_grad(void *self) { bool ret = _lantern_Tensor_requires_grad(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API unsigned int(LANTERN_PTR _lantern_Tensor_register_hook)(void *self, void *hook);
  HOST_API unsigned int lantern_Tensor_register_hook(void *self, void *hook) { unsigned int ret = _lantern_Tensor_register_hook(self, hook); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_new_hook)(void *(*fun)(void *, void *), void *custom);
  HOST_API void * lantern_new_hook(void *(*fun)(void *, void *), void *custom) { void * ret = _lantern_new_hook(fun, custom); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_Tensor_remove_hook)(void *self, unsigned int pos);
  HOST_API void lantern_Tensor_remove_hook(void *self, unsigned int pos) { _lantern_Tensor_remove_hook(self, pos); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_variable_list_new)();
  HOST_API void * lantern_variable_list_new() { void * ret = _lantern_variable_list_new(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_variable_list_push_back)(void *self, void *x);
  HOST_API void lantern_variable_list_push_back(void *self, void *x) { _lantern_variable_list_push_back(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_variable_list_get)(void *self, int64_t i);
  HOST_API void * lantern_variable_list_get(void *self, int64_t i) { void * ret = _lantern_variable_list_get(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_variable_list_delete)(void *x);
  HOST_API void lantern_variable_list_delete(void *x) { _lantern_variable_list_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API int64_t(LANTERN_PTR _lantern_variable_list_size)(void *self);
  HOST_API int64_t lantern_variable_list_size(void *self) { int64_t ret = _lantern_variable_list_size(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Function_lambda)(void *(*fun)(void *, void *, void *), void *custom);
  HOST_API void * lantern_Function_lambda(void *(*fun)(void *, void *, void *), void *custom) { void * ret = _lantern_Function_lambda(fun, custom); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Function_apply)(void *inputs, void *forward, void *backward);
  HOST_API void * lantern_Function_apply(void *inputs, void *forward, void *backward) { void * ret = _lantern_Function_apply(inputs, forward, backward); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_AutogradContext_save_for_backward)(void *self, void *vars);
  HOST_API void lantern_AutogradContext_save_for_backward(void *self, void *vars) { _lantern_AutogradContext_save_for_backward(self, vars); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_AutogradContext_get_saved_variables)(void *self);
  HOST_API void * lantern_AutogradContext_get_saved_variables(void *self) { void * ret = _lantern_AutogradContext_get_saved_variables(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_vector_string_new)();
  HOST_API void * lantern_vector_string_new() { void * ret = _lantern_vector_string_new(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_vector_string_push_back)(void *self, const char *x);
  HOST_API void lantern_vector_string_push_back(void *self, const char *x) { _lantern_vector_string_push_back(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API int64_t(LANTERN_PTR _lantern_vector_string_size)(void *self);
  HOST_API int64_t lantern_vector_string_size(void *self) { int64_t ret = _lantern_vector_string_size(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_vector_string_at)(void *self, int64_t i);
  HOST_API const char * lantern_vector_string_at(void *self, int64_t i) { const char * ret = _lantern_vector_string_at(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_vector_bool_new)();
  HOST_API void * lantern_vector_bool_new() { void * ret = _lantern_vector_bool_new(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_vector_bool_push_back)(void *self, bool x);
  HOST_API void lantern_vector_bool_push_back(void *self, bool x) { _lantern_vector_bool_push_back(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API int64_t(LANTERN_PTR _lantern_vector_bool_size)(void *self);
  HOST_API int64_t lantern_vector_bool_size(void *self) { int64_t ret = _lantern_vector_bool_size(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_vector_bool_at)(void *self, int64_t i);
  HOST_API bool lantern_vector_bool_at(void *self, int64_t i) { bool ret = _lantern_vector_bool_at(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_AutogradContext_set_arguments)(void *self, void *names, void *needs_grad);
  HOST_API void lantern_AutogradContext_set_arguments(void *self, void *names, void *needs_grad) { _lantern_AutogradContext_set_arguments(self, names, needs_grad); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_AutogradContext_get_argument_names)(void *self);
  HOST_API void * lantern_AutogradContext_get_argument_names(void *self) { void * ret = _lantern_AutogradContext_get_argument_names(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_AutogradContext_get_argument_needs_grad)(void *self);
  HOST_API void * lantern_AutogradContext_get_argument_needs_grad(void *self) { void * ret = _lantern_AutogradContext_get_argument_needs_grad(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_AutogradContext_set_saved_variables_names)(void *self, void *names);
  HOST_API void lantern_AutogradContext_set_saved_variables_names(void *self, void *names) { _lantern_AutogradContext_set_saved_variables_names(self, names); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_AutogradContext_get_saved_variables_names)(void *self);
  HOST_API void * lantern_AutogradContext_get_saved_variables_names(void *self) { void * ret = _lantern_AutogradContext_get_saved_variables_names(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_AutogradContext_mark_dirty)(void *self, void *inputs);
  HOST_API void lantern_AutogradContext_mark_dirty(void *self, void *inputs) { _lantern_AutogradContext_mark_dirty(self, inputs); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_AutogradContext_mark_non_differentiable)(void *self, void *outputs);
  HOST_API void lantern_AutogradContext_mark_non_differentiable(void *self, void *outputs) { _lantern_AutogradContext_mark_non_differentiable(self, outputs); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_optional_double)(double x, bool is_null);
  HOST_API void * lantern_optional_double(double x, bool is_null) { void * ret = _lantern_optional_double(x, is_null); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _test_grad_fn)();
  HOST_API void test_grad_fn(double x, bool is_null) { _test_grad_fn(); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_grad_fn)(void *self);
  HOST_API void * lantern_Tensor_grad_fn(void *self) { void * ret = _lantern_Tensor_grad_fn(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Node_name)(void *self);
  HOST_API const char * lantern_Node_name(void *self) { const char * ret = _lantern_Node_name(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Node_next_edges)(void *self);
  HOST_API void * lantern_Node_next_edges(void *self) { void * ret = _lantern_Node_next_edges(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_edge_list_size)(void *self);
  HOST_API int64_t lantern_edge_list_size(void *self) { int64_t ret = _lantern_edge_list_size(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_edge_list_at)(void *self, int64_t i);
  HOST_API void * lantern_edge_list_at(void *self, int64_t i) { void * ret = _lantern_edge_list_at(self, i); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Edge_function)(void *self);
  HOST_API void * lantern_Edge_function(void *self) { void * ret = _lantern_Edge_function(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_vector_int64_t_delete)(void *x);
  HOST_API void lantern_vector_int64_t_delete(void *x) { _lantern_vector_int64_t_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_autograd_backward)(void *tensors, void *grad_tensors, bool retain_graph, bool create_graph);
  HOST_API void lantern_autograd_backward(void *tensors, void *grad_tensors, bool retain_graph, bool create_graph) { _lantern_autograd_backward(tensors, grad_tensors, retain_graph, create_graph); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_autograd_grad)(void *outputs, void *inputs, void *grad_outputs, bool retain_graph, bool create_graph, bool allow_unused);
  HOST_API void * lantern_autograd_grad(void *outputs, void *inputs, void *grad_outputs, bool retain_graph, bool create_graph, bool allow_unused) { void * ret = _lantern_autograd_grad(outputs, inputs, grad_outputs, retain_graph, create_graph, allow_unused); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Layout_strided)();
  HOST_API void * lantern_Layout_strided() { void * ret = _lantern_Layout_strided(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Layout_sparse)();
  HOST_API void * lantern_Layout_sparse() { void * ret = _lantern_Layout_sparse(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Layout_string)(void *x);
  HOST_API const char * lantern_Layout_string(void *x) { const char * ret = _lantern_Layout_string(x); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_TensorIndex_new)();
  HOST_API void * lantern_TensorIndex_new() { void * ret = _lantern_TensorIndex_new(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_tensor)(void *self, void *x);
  HOST_API void lantern_TensorIndex_append_tensor(void *self, void *x) { _lantern_TensorIndex_append_tensor(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_ellipsis)(void *self);
  HOST_API void lantern_TensorIndex_append_ellipsis(void *self) { _lantern_TensorIndex_append_ellipsis(self); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_slice)(void *self, void *x);
  HOST_API void lantern_TensorIndex_append_slice(void *self, void *x) { _lantern_TensorIndex_append_slice(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_none)(void *self);
  HOST_API void lantern_TensorIndex_append_none(void *self) { _lantern_TensorIndex_append_none(self); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_bool)(void *self, bool x);
  HOST_API void lantern_TensorIndex_append_bool(void *self, bool x) { _lantern_TensorIndex_append_bool(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_append_int64)(void *self, int64_t x);
  HOST_API void lantern_TensorIndex_append_int64(void *self, int64_t x) { _lantern_TensorIndex_append_int64(self, x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_index)(void *self, void *index);
  HOST_API void * lantern_Tensor_index(void *self, void *index) { void * ret = _lantern_Tensor_index(self, index); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_TensorIndex_delete)(void *x);
  HOST_API void lantern_TensorIndex_delete(void *x) { _lantern_TensorIndex_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Slice)(void *start, void *end, void *step);
  HOST_API void * lantern_Slice(void *start, void *end, void *step) { void * ret = _lantern_Slice(start, end, step); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_optional_int64_t)(int64_t x, bool is_null);
  HOST_API void * lantern_optional_int64_t(int64_t x, bool is_null) { void * ret = _lantern_optional_int64_t(x, is_null); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_Slice_delete)(void *x);
  HOST_API void lantern_Slice_delete(void *x) { _lantern_Slice_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void(LANTERN_PTR _lantern_optional_int64_t_delete)(void *x);
  HOST_API void lantern_optional_int64_t_delete(void *x) { _lantern_optional_int64_t_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_device)(void *self);
  HOST_API void * lantern_Tensor_device(void *self) { void * ret = _lantern_Tensor_device(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_cuda_is_available)();
  HOST_API bool lantern_cuda_is_available() { bool ret = _lantern_cuda_is_available(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int(LANTERN_PTR _lantern_cuda_device_count)();
  HOST_API int lantern_cuda_device_count() { int ret = _lantern_cuda_device_count(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int64_t(LANTERN_PTR _lantern_cuda_current_device)();
  HOST_API int64_t lantern_cuda_current_device() { int64_t ret = _lantern_cuda_current_device(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_cuda_show_config)();
  HOST_API void lantern_cuda_show_config() { _lantern_cuda_show_config(); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_rnn_pack_padded_sequence)(void *input, void *lengths, bool batch_first, bool enforce_sorted);
  HOST_API void * lantern_nn_utils_rnn_pack_padded_sequence(void *input, void *lengths, bool batch_first, bool enforce_sorted) { void * ret = _lantern_nn_utils_rnn_pack_padded_sequence(input, lengths, batch_first, enforce_sorted); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_PackedSequence_delete)(void *x);
  HOST_API void lantern_PackedSequence_delete(void *x) { _lantern_PackedSequence_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_PackedSequence_batch_sizes)(void *input);
  HOST_API void * lantern_nn_utils_PackedSequence_batch_sizes(void *input) { void * ret = _lantern_nn_utils_PackedSequence_batch_sizes(input); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_PackedSequence_data)(void *input);
  HOST_API void * lantern_nn_utils_PackedSequence_data(void *input) { void * ret = _lantern_nn_utils_PackedSequence_data(input); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_PackedSequence_sorted_indices)(void *input);
  HOST_API void * lantern_nn_utils_PackedSequence_sorted_indices(void *input) { void * ret = _lantern_nn_utils_PackedSequence_sorted_indices(input); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_PackedSequence_unsorted_indices)(void *input);
  HOST_API void * lantern_nn_utils_PackedSequence_unsorted_indices(void *input) { void * ret = _lantern_nn_utils_PackedSequence_unsorted_indices(input); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_rnn_pack_sequence)(void *sequence, bool enforce_sorted);
  HOST_API void * lantern_nn_utils_rnn_pack_sequence(void *sequence, bool enforce_sorted) { void * ret = _lantern_nn_utils_rnn_pack_sequence(sequence, enforce_sorted); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_rnn_pad_packed_sequence)(void *sequence, bool batch_first, double padding_value, void *total_length);
  HOST_API void * lantern_nn_utils_rnn_pad_packed_sequence(void *sequence, bool batch_first, double padding_value, void *total_length) { void * ret = _lantern_nn_utils_rnn_pad_packed_sequence(sequence, batch_first, padding_value, total_length); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_rnn_pad_sequence)(void *sequence, bool batch_first, double padding_value);
  HOST_API void * lantern_nn_utils_rnn_pad_sequence(void *sequence, bool batch_first, double padding_value) { void * ret = _lantern_nn_utils_rnn_pad_sequence(sequence, batch_first, padding_value); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_nn_utils_rnn_PackedSequence_new)(void *data, void *batch_sizes, void *sorted_indices, void *unsorted_indices);
  HOST_API void * lantern_nn_utils_rnn_PackedSequence_new(void *data, void *batch_sizes, void *sorted_indices, void *unsorted_indices) { void * ret = _lantern_nn_utils_rnn_PackedSequence_new(data, batch_sizes, sorted_indices, unsorted_indices); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void *(LANTERN_PTR _lantern_Scalar_dtype)(void *self);
  HOST_API void * lantern_Scalar_dtype(void *self) { void * ret = _lantern_Scalar_dtype(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API float(LANTERN_PTR _lantern_Scalar_to_float)(void *self);
  HOST_API float lantern_Scalar_to_float(void *self) { float ret = _lantern_Scalar_to_float(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API int(LANTERN_PTR _lantern_Scalar_to_int)(void *self);
  HOST_API int lantern_Scalar_to_int(void *self) { int ret = _lantern_Scalar_to_int(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API double(LANTERN_PTR _lantern_Scalar_to_double)(void *self);
  HOST_API double lantern_Scalar_to_double(void *self) { double ret = _lantern_Scalar_to_double(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_Scalar_to_bool)(void *self);
  HOST_API bool lantern_Scalar_to_bool(void *self) { bool ret = _lantern_Scalar_to_bool(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_Tensor_is_undefined)(void *self);
  HOST_API bool lantern_Tensor_is_undefined(void *self) { bool ret = _lantern_Tensor_is_undefined(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_set_default_dtype)(void *dtype);
  HOST_API void lantern_set_default_dtype(void *dtype) { _lantern_set_default_dtype(dtype); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_get_default_dtype)();
  HOST_API void * lantern_get_default_dtype() { void * ret = _lantern_get_default_dtype(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void (LANTERN_PTR _lantern_Tensor_set_grad_)(void* self, void* new_grad);
  HOST_API void lantern_Tensor_set_grad_(void* self, void* new_grad) { _lantern_Tensor_set_grad_(self, new_grad); LANTERN_HOST_HANDLER }
  LANTERN_API void *(LANTERN_PTR _lantern_Tensor_storage)(void *self);
  HOST_API void * lantern_Tensor_storage(void *self) { void * ret = _lantern_Tensor_storage(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API bool(LANTERN_PTR _lantern_Tensor_has_storage)(void *self);
  HOST_API bool lantern_Tensor_has_storage(void *self) { bool ret = _lantern_Tensor_has_storage(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char *(LANTERN_PTR _lantern_Storage_data_ptr)(void *self);
  HOST_API const char * lantern_Storage_data_ptr(void *self) { const char * ret = _lantern_Storage_data_ptr(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void(LANTERN_PTR _lantern_Storage_delete)(void *x);
  HOST_API void lantern_Storage_delete(void *x) { _lantern_Storage_delete(x); LANTERN_HOST_HANDLER }
  LANTERN_API bool(LANTERN_PTR _lantern_Tensor_is_contiguous)(void *self);
  HOST_API bool lantern_Tensor_is_contiguous(void *self) { bool ret = _lantern_Tensor_is_contiguous(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API const char  * (LANTERN_PTR _lantern_tensor_save) (void* self);
  HOST_API const char  * lantern_tensor_save(void* self) { const char  * ret = _lantern_tensor_save(self); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void * (LANTERN_PTR _lantern_tensor_load) (const char * s);
  HOST_API void * lantern_tensor_load(const char * s) { void * ret = _lantern_tensor_load(s); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void * (LANTERN_PTR _lantern_test_tensor)();
  HOST_API void * lantern_test_tensor() { void * ret = _lantern_test_tensor(); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void (LANTERN_PTR _lantern_test_print)(void* x); 
  HOST_API void lantern_test_print(void* x) { _lantern_test_print(x); LANTERN_HOST_HANDLER }
  LANTERN_API size_t (LANTERN_PTR _lantern_tensor_serialized_size) (const char * s);
  HOST_API size_t lantern_tensor_serialized_size(const char * s) { size_t ret = _lantern_tensor_serialized_size(s); LANTERN_HOST_HANDLER return ret;}
  LANTERN_API void (LANTERN_PTR _lantern_const_char_delete) (const char * x);
  HOST_API void lantern_const_char_delete(const char * x) { return LANTERN_HOST_HANDLER(_lantern_const_char_delete(x)); }
  LANTERN_API void (LANTERN_PTR _lantern_Tensor_index_put_tensor_) (void* self, void* index, void* rhs);
  HOST_API void lantern_Tensor_index_put_tensor_ (void* self, void* index, void* rhs) { _lantern_Tensor_index_put_tensor_(self, index, rhs); LANTERN_HOST_HANDLER}
  LANTERN_API void (LANTERN_PTR _lantern_Tensor_index_put_scalar_) (void* self, void* index, void* rhs);
  HOST_API void lantern_Tensor_index_put_scalar_ (void* self, void* index, void* rhs) { _lantern_Tensor_index_put_scalar_(self, index, rhs); LANTERN_HOST_HANDLER}
  LANTERN_API void (LANTERN_PTR _lantern_manual_seed) (int64_t seed);
  HOST_API void lantern_manual_seed (int64_t seed) {_lantern_manual_seed(seed); LANTERN_HOST_HANDLER}

  LANTERN_API void* (LANTERN_PTR _lantern_load_state_dict) (const char * path);
  HOST_API void * lantern_load_state_dict (const char * path)
  {
    void * ret = _lantern_load_state_dict(path);
    LANTERN_HOST_HANDLER return ret;
  }

  LANTERN_API void* (LANTERN_PTR _lantern_get_state_dict_keys) (void * ivalue);
  HOST_API void* lantern_get_state_dict_keys (void* ivalue)
  {
    void * ret = _lantern_get_state_dict_keys(ivalue);
    LANTERN_HOST_HANDLER return ret;
  }

  LANTERN_API void* (LANTERN_PTR _lantern_get_state_dict_values) (void * ivalue);
  HOST_API void* lantern_get_state_dict_values (void* ivalue)
  {
    void * ret = _lantern_get_state_dict_values(ivalue);
    LANTERN_HOST_HANDLER return ret;
  }

  LANTERN_API void (LANTERN_PTR _lantern_IValue_delete) (void * x);
  HOST_API void lantern_IValue_delete (void* x)
  {
    _lantern_get_state_dict_values(x);
    LANTERN_HOST_HANDLER;
  }

  LANTERN_API void (LANTERN_PTR _lantern_vector_string_delete) (void * x);
  HOST_API void lantern_vector_string_delete (void* x)
  {
    _lantern_vector_string_delete(x);
    LANTERN_HOST_HANDLER;
  }

  LANTERN_API int64_t *(LANTERN_PTR _lantern_Tensor_data_ptr_int64_t)(void *self);
  HOST_API int64_t* lantern_Tensor_data_ptr_int64_t (void* self)
  {
    int64_t* ret = _lantern_Tensor_data_ptr_int64_t(self);
    LANTERN_HOST_HANDLER;
    return ret;
  }

  LANTERN_API bool  (LANTERN_PTR _lantern_Tensor_has_names) (void* self);
  HOST_API bool lantern_Tensor_has_names (void* self)
  {
    bool ret = _lantern_Tensor_has_names(self);
    LANTERN_HOST_HANDLER;
    return ret;
  }

  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_names) (void * self);
  HOST_API void* lantern_Tensor_names (void* self)
  {
    void* ret = _lantern_Tensor_names(self);
    LANTERN_HOST_HANDLER;
    return ret;
  }

  LANTERN_API void* (LANTERN_PTR _lantern_string_new) (const char * value);
  HOST_API void* lantern_string_new (const char* value)
  {
    void* ret = _lantern_string_new(value);
    LANTERN_HOST_HANDLER;
    return ret;
  }

  LANTERN_API void (LANTERN_PTR _lantern_string_delete) (void * x);
  HOST_API void lantern_string_delete (void* x)
  {
    _lantern_string_delete(x);
    LANTERN_HOST_HANDLER;
  }

  /* Autogen Headers -- Start */
  LANTERN_API void* (LANTERN_PTR _lantern__cast_byte_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_byte_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_byte_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_char_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_char_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_char_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_double_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_double_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_double_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_float_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_float_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_float_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_int_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_int_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_int_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_long_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_long_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_long_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_short_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_short_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_short_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cast_half_tensor_bool)(void* self, void* non_blocking);
  HOST_API void* lantern__cast_half_tensor_bool(void* self, void* non_blocking) { void* ret = _lantern__cast_half_tensor_bool(self, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_backward_tensor_tensor_bool_bool)(void* self, void* gradient, void* keep_graph, void* create_graph);
  HOST_API void* lantern_Tensor_backward_tensor_tensor_bool_bool(void* self, void* gradient, void* keep_graph, void* create_graph) { void* ret = _lantern_Tensor_backward_tensor_tensor_bool_bool(self, gradient, keep_graph, create_graph); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set_data_tensor_tensor)(void* self, void* new_data);
  HOST_API void* lantern_Tensor_set_data_tensor_tensor(void* self, void* new_data) { void* ret = _lantern_Tensor_set_data_tensor_tensor(self, new_data); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_data_tensor)(void* self);
  HOST_API void* lantern_Tensor_data_tensor(void* self) { void* ret = _lantern_Tensor_data_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_leaf_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_leaf_tensor(void* self) { void* ret = _lantern_Tensor_is_leaf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_output_nr_tensor)(void* self);
  HOST_API void* lantern_Tensor_output_nr_tensor(void* self) { void* ret = _lantern_Tensor_output_nr_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__version_tensor)(void* self);
  HOST_API void* lantern_Tensor__version_tensor(void* self) { void* ret = _lantern_Tensor__version_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_requires_grad__tensor_bool)(void* self, void* _requires_grad);
  HOST_API void* lantern_Tensor_requires_grad__tensor_bool(void* self, void* _requires_grad) { void* ret = _lantern_Tensor_requires_grad__tensor_bool(self, _requires_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_retain_grad_tensor)(void* self);
  HOST_API void* lantern_Tensor_retain_grad_tensor(void* self) { void* ret = _lantern_Tensor_retain_grad_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rename__tensor_dimnamelist)(void* self, void* names);
  HOST_API void* lantern_Tensor_rename__tensor_dimnamelist(void* self, void* names) { void* ret = _lantern_Tensor_rename__tensor_dimnamelist(self, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rename_tensor_dimnamelist)(void* self, void* names);
  HOST_API void* lantern_Tensor_rename_tensor_dimnamelist(void* self, void* names) { void* ret = _lantern_Tensor_rename_tensor_dimnamelist(self, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_align_to_tensor_dimnamelist)(void* self, void* names);
  HOST_API void* lantern_Tensor_align_to_tensor_dimnamelist(void* self, void* names) { void* ret = _lantern_Tensor_align_to_tensor_dimnamelist(self, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_align_to_tensor_dimnamelist_intt)(void* self, void* order, void* ellipsis_idx);
  HOST_API void* lantern_Tensor_align_to_tensor_dimnamelist_intt(void* self, void* order, void* ellipsis_idx) { void* ret = _lantern_Tensor_align_to_tensor_dimnamelist_intt(self, order, ellipsis_idx); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_align_as_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_align_as_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_align_as_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_align_tensors_tensorlist)(void* tensors);
  HOST_API void* lantern_align_tensors_tensorlist(void* tensors) { void* ret = _lantern_align_tensors_tensorlist(tensors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_refine_names_tensor_dimnamelist)(void* self, void* names);
  HOST_API void* lantern_Tensor_refine_names_tensor_dimnamelist(void* self, void* names) { void* ret = _lantern_Tensor_refine_names_tensor_dimnamelist(self, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unflatten_tensor_dimname_intarrayref_dimnamelist)(void* self, void* dim, void* sizes, void* names);
  HOST_API void* lantern_Tensor_unflatten_tensor_dimname_intarrayref_dimnamelist(void* self, void* dim, void* sizes, void* names) { void* ret = _lantern_Tensor_unflatten_tensor_dimname_intarrayref_dimnamelist(self, dim, sizes, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unflatten_tensor_intt_intarrayref_dimnamelist)(void* self, void* dim, void* sizes, void* names);
  HOST_API void* lantern_Tensor_unflatten_tensor_intt_intarrayref_dimnamelist(void* self, void* dim, void* sizes, void* names) { void* ret = _lantern_Tensor_unflatten_tensor_intt_intarrayref_dimnamelist(self, dim, sizes, names); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__use_cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt)(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank);
  HOST_API void* lantern__use_cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank) { void* ret = _lantern__use_cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt(log_probs, targets, input_lengths, target_lengths, blank); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool_bool)(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* deterministic, void* zero_infinity);
  HOST_API void* lantern__cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool_bool(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* deterministic, void* zero_infinity) { void* ret = _lantern__cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool_bool(log_probs, targets, input_lengths, target_lengths, blank, deterministic, zero_infinity); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__use_cudnn_rnn_flatten_weight)();
  HOST_API void* lantern__use_cudnn_rnn_flatten_weight() { void* ret = _lantern__use_cudnn_rnn_flatten_weight(); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cudnn_rnn_flatten_weight_tensorlist_intt_intt_intt_intt_intt_bool_bool)(void* weight_arr, void* weight_stride0, void* input_size, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* bidirectional);
  HOST_API void* lantern__cudnn_rnn_flatten_weight_tensorlist_intt_intt_intt_intt_intt_bool_bool(void* weight_arr, void* weight_stride0, void* input_size, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* bidirectional) { void* ret = _lantern__cudnn_rnn_flatten_weight_tensorlist_intt_intt_intt_intt_intt_bool_bool(weight_arr, weight_stride0, input_size, mode, hidden_size, num_layers, batch_first, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cudnn_rnn_tensor_tensorlist_intt_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor)(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state);
  HOST_API void* lantern__cudnn_rnn_tensor_tensorlist_intt_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state) { void* ret = _lantern__cudnn_rnn_tensor_tensorlist_intt_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor(input, weight, weight_stride0, weight_buf, hx, cx, mode, hidden_size, num_layers, batch_first, dropout, train, bidirectional, batch_sizes, dropout_state); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cudnn_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool)(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* output, void* grad_output, void* grad_hy, void* grad_cy, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state, void* reserve, void* output_mask);
  HOST_API void* lantern__cudnn_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* output, void* grad_output, void* grad_hy, void* grad_cy, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state, void* reserve, void* output_mask) { void* ret = _lantern__cudnn_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool(input, weight, weight_stride0, weight_buf, hx, cx, output, grad_output, grad_hy, grad_cy, mode, hidden_size, num_layers, batch_first, dropout, train, bidirectional, batch_sizes, dropout_state, reserve, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cudnn_init_dropout_state_double_bool_intt_tensoroptions)(void* dropout, void* train, void* dropout_seed, void* options);
  HOST_API void* lantern__cudnn_init_dropout_state_double_bool_intt_tensoroptions(void* dropout, void* train, void* dropout_seed, void* options) { void* ret = _lantern__cudnn_init_dropout_state_double_bool_intt_tensoroptions(dropout, train, dropout_seed, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__debug_has_internal_overlap_tensor)(void* self);
  HOST_API void* lantern__debug_has_internal_overlap_tensor(void* self) { void* ret = _lantern__debug_has_internal_overlap_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__fused_dropout_tensor_double_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern__fused_dropout_tensor_double_generator(void* self, void* p, void* generator) { void* ret = _lantern__fused_dropout_tensor_double_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__masked_scale_tensor_tensor_double)(void* self, void* mask, void* scale);
  HOST_API void* lantern__masked_scale_tensor_tensor_double(void* self, void* mask, void* scale) { void* ret = _lantern__masked_scale_tensor_tensor_double(self, mask, scale); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sobol_engine_draw_tensor_intt_tensor_intt_intt_scalartype)(void* quasi, void* n, void* sobolstate, void* dimension, void* num_generated, void* dtype);
  HOST_API void* lantern__sobol_engine_draw_tensor_intt_tensor_intt_intt_scalartype(void* quasi, void* n, void* sobolstate, void* dimension, void* num_generated, void* dtype) { void* ret = _lantern__sobol_engine_draw_tensor_intt_tensor_intt_intt_scalartype(quasi, n, sobolstate, dimension, num_generated, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sobol_engine_ff__tensor_intt_tensor_intt_intt)(void* self, void* n, void* sobolstate, void* dimension, void* num_generated);
  HOST_API void* lantern__sobol_engine_ff__tensor_intt_tensor_intt_intt(void* self, void* n, void* sobolstate, void* dimension, void* num_generated) { void* ret = _lantern__sobol_engine_ff__tensor_intt_tensor_intt_intt(self, n, sobolstate, dimension, num_generated); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sobol_engine_scramble__tensor_tensor_intt)(void* self, void* ltm, void* dimension);
  HOST_API void* lantern__sobol_engine_scramble__tensor_tensor_intt(void* self, void* ltm, void* dimension) { void* ret = _lantern__sobol_engine_scramble__tensor_tensor_intt(self, ltm, dimension); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sobol_engine_initialize_state__tensor_intt)(void* self, void* dimension);
  HOST_API void* lantern__sobol_engine_initialize_state__tensor_intt(void* self, void* dimension) { void* ret = _lantern__sobol_engine_initialize_state__tensor_intt(self, dimension); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__reshape_from_tensor_tensor_tensor)(void* self, void* shape);
  HOST_API void* lantern__reshape_from_tensor_tensor_tensor(void* self, void* shape) { void* ret = _lantern__reshape_from_tensor_tensor_tensor(self, shape); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__shape_as_tensor_tensor)(void* self);
  HOST_API void* lantern__shape_as_tensor_tensor(void* self) { void* ret = _lantern__shape_as_tensor_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dropout_tensor_double_bool)(void* input, void* p, void* train);
  HOST_API void* lantern_dropout_tensor_double_bool(void* input, void* p, void* train) { void* ret = _lantern_dropout_tensor_double_bool(input, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dropout__tensor_double_bool)(void* self, void* p, void* train);
  HOST_API void* lantern_dropout__tensor_double_bool(void* self, void* p, void* train) { void* ret = _lantern_dropout__tensor_double_bool(self, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_feature_dropout_tensor_double_bool)(void* input, void* p, void* train);
  HOST_API void* lantern_feature_dropout_tensor_double_bool(void* input, void* p, void* train) { void* ret = _lantern_feature_dropout_tensor_double_bool(input, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_feature_dropout__tensor_double_bool)(void* self, void* p, void* train);
  HOST_API void* lantern_feature_dropout__tensor_double_bool(void* self, void* p, void* train) { void* ret = _lantern_feature_dropout__tensor_double_bool(self, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_alpha_dropout_tensor_double_bool)(void* input, void* p, void* train);
  HOST_API void* lantern_alpha_dropout_tensor_double_bool(void* input, void* p, void* train) { void* ret = _lantern_alpha_dropout_tensor_double_bool(input, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_alpha_dropout__tensor_double_bool)(void* self, void* p, void* train);
  HOST_API void* lantern_alpha_dropout__tensor_double_bool(void* self, void* p, void* train) { void* ret = _lantern_alpha_dropout__tensor_double_bool(self, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_feature_alpha_dropout_tensor_double_bool)(void* input, void* p, void* train);
  HOST_API void* lantern_feature_alpha_dropout_tensor_double_bool(void* input, void* p, void* train) { void* ret = _lantern_feature_alpha_dropout_tensor_double_bool(input, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_feature_alpha_dropout__tensor_double_bool)(void* self, void* p, void* train);
  HOST_API void* lantern_feature_alpha_dropout__tensor_double_bool(void* self, void* p, void* train) { void* ret = _lantern_feature_alpha_dropout__tensor_double_bool(self, p, train); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_abs_tensor)(void* self);
  HOST_API void* lantern_abs_tensor(void* self) { void* ret = _lantern_abs_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_abs_tensor)(void* self);
  HOST_API void* lantern_Tensor_abs_tensor(void* self) { void* ret = _lantern_Tensor_abs_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_abs__tensor)(void* self);
  HOST_API void* lantern_abs__tensor(void* self) { void* ret = _lantern_abs__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_abs__tensor)(void* self);
  HOST_API void* lantern_Tensor_abs__tensor(void* self) { void* ret = _lantern_Tensor_abs__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_abs_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_abs_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_abs_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_angle_tensor)(void* self);
  HOST_API void* lantern_angle_tensor(void* self) { void* ret = _lantern_angle_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_angle_tensor)(void* self);
  HOST_API void* lantern_Tensor_angle_tensor(void* self) { void* ret = _lantern_Tensor_angle_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_angle_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_angle_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_angle_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_real_tensor)(void* self);
  HOST_API void* lantern_real_tensor(void* self) { void* ret = _lantern_real_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_imag_tensor)(void* self);
  HOST_API void* lantern_imag_tensor(void* self) { void* ret = _lantern_imag_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conj_tensor)(void* self);
  HOST_API void* lantern_conj_tensor(void* self) { void* ret = _lantern_conj_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_conj_tensor)(void* self);
  HOST_API void* lantern_Tensor_conj_tensor(void* self) { void* ret = _lantern_Tensor_conj_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conj_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_conj_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_conj_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_acos_tensor)(void* self);
  HOST_API void* lantern_acos_tensor(void* self) { void* ret = _lantern_acos_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_acos_tensor)(void* self);
  HOST_API void* lantern_Tensor_acos_tensor(void* self) { void* ret = _lantern_Tensor_acos_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_acos__tensor)(void* self);
  HOST_API void* lantern_acos__tensor(void* self) { void* ret = _lantern_acos__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_acos__tensor)(void* self);
  HOST_API void* lantern_Tensor_acos__tensor(void* self) { void* ret = _lantern_Tensor_acos__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_acos_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_acos_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_acos_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool1d_tensor_intarrayref_intarrayref_intarrayref_bool_bool)(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad);
  HOST_API void* lantern_avg_pool1d_tensor_intarrayref_intarrayref_intarrayref_bool_bool(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad) { void* ret = _lantern_avg_pool1d_tensor_intarrayref_intarrayref_intarrayref_bool_bool(self, kernel_size, stride, padding, ceil_mode, count_include_pad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool1d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_avg_pool1d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_avg_pool1d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool1d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_max_pool1d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_max_pool1d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_add_tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_add_tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_add_tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_add_tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_add_tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_add_tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_add__tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_add__tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_add__tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_add_out_tensor_tensor_tensor_scalar)(void* out, void* self, void* other, void* alpha);
  HOST_API void* lantern_add_out_tensor_tensor_tensor_scalar(void* out, void* self, void* other, void* alpha) { void* ret = _lantern_add_out_tensor_tensor_tensor_scalar(out, self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_add_tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_add_tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_add_tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_add_tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_add_tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_add_tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_add__tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_add__tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_add__tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addmv_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat, void* vec, void* beta, void* alpha);
  HOST_API void* lantern_addmv_tensor_tensor_tensor_scalar_scalar(void* self, void* mat, void* vec, void* beta, void* alpha) { void* ret = _lantern_addmv_tensor_tensor_tensor_scalar_scalar(self, mat, vec, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addmv_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat, void* vec, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addmv_tensor_tensor_tensor_scalar_scalar(void* self, void* mat, void* vec, void* beta, void* alpha) { void* ret = _lantern_Tensor_addmv_tensor_tensor_tensor_scalar_scalar(self, mat, vec, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addmv__tensor_tensor_tensor_scalar_scalar)(void* self, void* mat, void* vec, void* beta, void* alpha);
  HOST_API void* lantern_addmv__tensor_tensor_tensor_scalar_scalar(void* self, void* mat, void* vec, void* beta, void* alpha) { void* ret = _lantern_addmv__tensor_tensor_tensor_scalar_scalar(self, mat, vec, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addmv__tensor_tensor_tensor_scalar_scalar)(void* self, void* mat, void* vec, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addmv__tensor_tensor_tensor_scalar_scalar(void* self, void* mat, void* vec, void* beta, void* alpha) { void* ret = _lantern_Tensor_addmv__tensor_tensor_tensor_scalar_scalar(self, mat, vec, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addmv_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* mat, void* vec, void* beta, void* alpha);
  HOST_API void* lantern_addmv_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* mat, void* vec, void* beta, void* alpha) { void* ret = _lantern_addmv_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, mat, vec, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addr_tensor_tensor_tensor_scalar_scalar)(void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern_addr_tensor_tensor_tensor_scalar_scalar(void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern_addr_tensor_tensor_tensor_scalar_scalar(self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addr_tensor_tensor_tensor_scalar_scalar)(void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addr_tensor_tensor_tensor_scalar_scalar(void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addr_tensor_tensor_tensor_scalar_scalar(self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addr__tensor_tensor_tensor_scalar_scalar)(void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addr__tensor_tensor_tensor_scalar_scalar(void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addr__tensor_tensor_tensor_scalar_scalar(self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addr_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern_addr_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern_addr_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_affine_grid_generator_tensor_intarrayref_bool)(void* theta, void* size, void* align_corners);
  HOST_API void* lantern_affine_grid_generator_tensor_intarrayref_bool(void* theta, void* size, void* align_corners) { void* ret = _lantern_affine_grid_generator_tensor_intarrayref_bool(theta, size, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_affine_grid_generator_backward_tensor_intarrayref_bool)(void* grad, void* size, void* align_corners);
  HOST_API void* lantern_affine_grid_generator_backward_tensor_intarrayref_bool(void* grad, void* size, void* align_corners) { void* ret = _lantern_affine_grid_generator_backward_tensor_intarrayref_bool(grad, size, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_all_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_all_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_all_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_all_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_all_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_all_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_all_out_tensor_tensor_intt_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_all_out_tensor_tensor_intt_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_all_out_tensor_tensor_intt_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_all_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_all_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_all_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_all_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_all_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_all_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_all_out_tensor_tensor_dimname_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_all_out_tensor_tensor_dimname_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_all_out_tensor_tensor_dimname_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_allclose_tensor_tensor_double_double_bool)(void* self, void* other, void* rtol, void* atol, void* equal_nan);
  HOST_API void* lantern_allclose_tensor_tensor_double_double_bool(void* self, void* other, void* rtol, void* atol, void* equal_nan) { void* ret = _lantern_allclose_tensor_tensor_double_double_bool(self, other, rtol, atol, equal_nan); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_allclose_tensor_tensor_double_double_bool)(void* self, void* other, void* rtol, void* atol, void* equal_nan);
  HOST_API void* lantern_Tensor_allclose_tensor_tensor_double_double_bool(void* self, void* other, void* rtol, void* atol, void* equal_nan) { void* ret = _lantern_Tensor_allclose_tensor_tensor_double_double_bool(self, other, rtol, atol, equal_nan); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_any_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_any_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_any_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_any_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_any_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_any_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_any_out_tensor_tensor_intt_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_any_out_tensor_tensor_intt_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_any_out_tensor_tensor_intt_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_any_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_any_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_any_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_any_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_any_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_any_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_any_out_tensor_tensor_dimname_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_any_out_tensor_tensor_dimname_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_any_out_tensor_tensor_dimname_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_arange_scalar_tensoroptions)(void* end, void* options);
  HOST_API void* lantern_arange_scalar_tensoroptions(void* end, void* options) { void* ret = _lantern_arange_scalar_tensoroptions(end, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_arange_scalar_scalar_tensoroptions)(void* start, void* end, void* options);
  HOST_API void* lantern_arange_scalar_scalar_tensoroptions(void* start, void* end, void* options) { void* ret = _lantern_arange_scalar_scalar_tensoroptions(start, end, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_arange_scalar_scalar_scalar_tensoroptions)(void* start, void* end, void* step, void* options);
  HOST_API void* lantern_arange_scalar_scalar_scalar_tensoroptions(void* start, void* end, void* step, void* options) { void* ret = _lantern_arange_scalar_scalar_scalar_tensoroptions(start, end, step, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_arange_out_tensor_scalar)(void* out, void* end);
  HOST_API void* lantern_arange_out_tensor_scalar(void* out, void* end) { void* ret = _lantern_arange_out_tensor_scalar(out, end); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_arange_out_tensor_scalar_scalar_scalar)(void* out, void* start, void* end, void* step);
  HOST_API void* lantern_arange_out_tensor_scalar_scalar_scalar(void* out, void* start, void* end, void* step) { void* ret = _lantern_arange_out_tensor_scalar_scalar_scalar(out, start, end, step); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__dim_arange_tensor_intt)(void* like, void* dim);
  HOST_API void* lantern__dim_arange_tensor_intt(void* like, void* dim) { void* ret = _lantern__dim_arange_tensor_intt(like, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_argmax_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_argmax_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_argmax_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_argmax_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_argmax_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_argmax_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_argmin_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_argmin_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_argmin_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_argmin_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_argmin_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_argmin_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_as_strided_tensor_intarrayref_intarrayref_intt)(void* self, void* size, void* stride, void* storage_offset);
  HOST_API void* lantern_as_strided_tensor_intarrayref_intarrayref_intt(void* self, void* size, void* stride, void* storage_offset) { void* ret = _lantern_as_strided_tensor_intarrayref_intarrayref_intt(self, size, stride, storage_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_as_strided_tensor_intarrayref_intarrayref_intt)(void* self, void* size, void* stride, void* storage_offset);
  HOST_API void* lantern_Tensor_as_strided_tensor_intarrayref_intarrayref_intt(void* self, void* size, void* stride, void* storage_offset) { void* ret = _lantern_Tensor_as_strided_tensor_intarrayref_intarrayref_intt(self, size, stride, storage_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_as_strided__tensor_intarrayref_intarrayref_intt)(void* self, void* size, void* stride, void* storage_offset);
  HOST_API void* lantern_as_strided__tensor_intarrayref_intarrayref_intt(void* self, void* size, void* stride, void* storage_offset) { void* ret = _lantern_as_strided__tensor_intarrayref_intarrayref_intt(self, size, stride, storage_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_as_strided__tensor_intarrayref_intarrayref_intt)(void* self, void* size, void* stride, void* storage_offset);
  HOST_API void* lantern_Tensor_as_strided__tensor_intarrayref_intarrayref_intt(void* self, void* size, void* stride, void* storage_offset) { void* ret = _lantern_Tensor_as_strided__tensor_intarrayref_intarrayref_intt(self, size, stride, storage_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_asin_tensor)(void* self);
  HOST_API void* lantern_asin_tensor(void* self) { void* ret = _lantern_asin_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_asin_tensor)(void* self);
  HOST_API void* lantern_Tensor_asin_tensor(void* self) { void* ret = _lantern_Tensor_asin_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_asin__tensor)(void* self);
  HOST_API void* lantern_asin__tensor(void* self) { void* ret = _lantern_asin__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_asin__tensor)(void* self);
  HOST_API void* lantern_Tensor_asin__tensor(void* self) { void* ret = _lantern_Tensor_asin__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_asin_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_asin_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_asin_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_atan_tensor)(void* self);
  HOST_API void* lantern_atan_tensor(void* self) { void* ret = _lantern_atan_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_atan_tensor)(void* self);
  HOST_API void* lantern_Tensor_atan_tensor(void* self) { void* ret = _lantern_Tensor_atan_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_atan__tensor)(void* self);
  HOST_API void* lantern_atan__tensor(void* self) { void* ret = _lantern_atan__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_atan__tensor)(void* self);
  HOST_API void* lantern_Tensor_atan__tensor(void* self) { void* ret = _lantern_Tensor_atan__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_atan_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_atan_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_atan_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_baddbmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_baddbmm_tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_baddbmm_tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_baddbmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_baddbmm_tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_Tensor_baddbmm_tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_baddbmm__tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_baddbmm__tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_Tensor_baddbmm__tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__baddbmm_mkl__tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern__baddbmm_mkl__tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern__baddbmm_mkl__tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_baddbmm_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_baddbmm_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_baddbmm_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bartlett_window_intt_tensoroptions)(void* window_length, void* options);
  HOST_API void* lantern_bartlett_window_intt_tensoroptions(void* window_length, void* options) { void* ret = _lantern_bartlett_window_intt_tensoroptions(window_length, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bartlett_window_intt_bool_tensoroptions)(void* window_length, void* periodic, void* options);
  HOST_API void* lantern_bartlett_window_intt_bool_tensoroptions(void* window_length, void* periodic, void* options) { void* ret = _lantern_bartlett_window_intt_bool_tensoroptions(window_length, periodic, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps, void* cudnn_enabled);
  HOST_API void* lantern_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps, void* cudnn_enabled) { void* ret = _lantern_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(input, weight, bias, running_mean, running_var, training, momentum, eps, cudnn_enabled); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_batch_norm_tensor_tensor_tensor_tensor_tensor_double_double_intt)(void* input, void* weight, void* bias, void* mean, void* var, void* eps, void* output_scale, void* output_zero_point);
  HOST_API void* lantern_quantized_batch_norm_tensor_tensor_tensor_tensor_tensor_double_double_intt(void* input, void* weight, void* bias, void* mean, void* var, void* eps, void* output_scale, void* output_zero_point) { void* ret = _lantern_quantized_batch_norm_tensor_tensor_tensor_tensor_tensor_double_double_intt(input, weight, bias, mean, var, eps, output_scale, output_zero_point); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__batch_norm_impl_index_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps, void* cudnn_enabled);
  HOST_API void* lantern__batch_norm_impl_index_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps, void* cudnn_enabled) { void* ret = _lantern__batch_norm_impl_index_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(input, weight, bias, running_mean, running_var, training, momentum, eps, cudnn_enabled); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__batch_norm_impl_index_backward_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool_tensor)(void* impl_index, void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var_transform, void* train, void* eps, void* output_mask, void* reservedSpace);
  HOST_API void* lantern__batch_norm_impl_index_backward_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool_tensor(void* impl_index, void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var_transform, void* train, void* eps, void* output_mask, void* reservedSpace) { void* ret = _lantern__batch_norm_impl_index_backward_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool_tensor(impl_index, input, grad_output, weight, running_mean, running_var, save_mean, save_var_transform, train, eps, output_mask, reservedSpace); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bernoulli_tensor_generator)(void* self, void* generator);
  HOST_API void* lantern_bernoulli_tensor_generator(void* self, void* generator) { void* ret = _lantern_bernoulli_tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bernoulli_tensor_generator)(void* self, void* generator);
  HOST_API void* lantern_Tensor_bernoulli_tensor_generator(void* self, void* generator) { void* ret = _lantern_Tensor_bernoulli_tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bernoulli_out_tensor_tensor_generator)(void* out, void* self, void* generator);
  HOST_API void* lantern_bernoulli_out_tensor_tensor_generator(void* out, void* self, void* generator) { void* ret = _lantern_bernoulli_out_tensor_tensor_generator(out, self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bernoulli__tensor_tensor_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern_Tensor_bernoulli__tensor_tensor_generator(void* self, void* p, void* generator) { void* ret = _lantern_Tensor_bernoulli__tensor_tensor_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bernoulli__tensor_double_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern_Tensor_bernoulli__tensor_double_generator(void* self, void* p, void* generator) { void* ret = _lantern_Tensor_bernoulli__tensor_double_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bernoulli_tensor_double_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern_bernoulli_tensor_double_generator(void* self, void* p, void* generator) { void* ret = _lantern_bernoulli_tensor_double_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bernoulli_tensor_double_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern_Tensor_bernoulli_tensor_double_generator(void* self, void* p, void* generator) { void* ret = _lantern_Tensor_bernoulli_tensor_double_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bilinear_tensor_tensor_tensor_tensor)(void* input1, void* input2, void* weight, void* bias);
  HOST_API void* lantern_bilinear_tensor_tensor_tensor_tensor(void* input1, void* input2, void* weight, void* bias) { void* ret = _lantern_bilinear_tensor_tensor_tensor_tensor(input1, input2, weight, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_tensor_tensor_tensor_intt)(void* self, void* target, void* weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_tensor_tensor_tensor_intt(void* self, void* target, void* weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_tensor_tensor_tensor_intt(self, target, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_out_tensor_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_out_tensor_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_out_tensor_tensor_tensor_tensor_intt(out, self, target, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_backward_tensor_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_backward_tensor_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_backward_tensor_tensor_tensor_tensor_intt(grad_output, self, target, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_backward_out_tensor_tensor_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_backward_out_tensor_tensor_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_backward_out_tensor_tensor_tensor_tensor_tensor_intt(grad_input, grad_output, self, target, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_with_logits_tensor_tensor_tensor_tensor_intt)(void* self, void* target, void* weight, void* pos_weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_with_logits_tensor_tensor_tensor_tensor_intt(void* self, void* target, void* weight, void* pos_weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_with_logits_tensor_tensor_tensor_tensor_intt(self, target, weight, pos_weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_binary_cross_entropy_with_logits_backward_tensor_tensor_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* weight, void* pos_weight, void* reduction);
  HOST_API void* lantern_binary_cross_entropy_with_logits_backward_tensor_tensor_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* weight, void* pos_weight, void* reduction) { void* ret = _lantern_binary_cross_entropy_with_logits_backward_tensor_tensor_tensor_tensor_tensor_intt(grad_output, self, target, weight, pos_weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bincount_tensor_tensor_intt)(void* self, void* weights, void* minlength);
  HOST_API void* lantern_bincount_tensor_tensor_intt(void* self, void* weights, void* minlength) { void* ret = _lantern_bincount_tensor_tensor_intt(self, weights, minlength); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bincount_tensor_tensor_intt)(void* self, void* weights, void* minlength);
  HOST_API void* lantern_Tensor_bincount_tensor_tensor_intt(void* self, void* weights, void* minlength) { void* ret = _lantern_Tensor_bincount_tensor_tensor_intt(self, weights, minlength); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_not_tensor)(void* self);
  HOST_API void* lantern_bitwise_not_tensor(void* self) { void* ret = _lantern_bitwise_not_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_not_tensor)(void* self);
  HOST_API void* lantern_Tensor_bitwise_not_tensor(void* self) { void* ret = _lantern_Tensor_bitwise_not_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_not__tensor)(void* self);
  HOST_API void* lantern_Tensor_bitwise_not__tensor(void* self) { void* ret = _lantern_Tensor_bitwise_not__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_not_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_bitwise_not_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_bitwise_not_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_not_tensor)(void* self);
  HOST_API void* lantern_logical_not_tensor(void* self) { void* ret = _lantern_logical_not_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_not_tensor)(void* self);
  HOST_API void* lantern_Tensor_logical_not_tensor(void* self) { void* ret = _lantern_Tensor_logical_not_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_not__tensor)(void* self);
  HOST_API void* lantern_Tensor_logical_not__tensor(void* self) { void* ret = _lantern_Tensor_logical_not__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_not_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_logical_not_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_logical_not_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_xor_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_logical_xor_tensor_tensor(void* self, void* other) { void* ret = _lantern_logical_xor_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_xor_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_xor_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_xor_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_xor__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_xor__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_xor__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_xor_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_logical_xor_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_logical_xor_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_and_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_logical_and_tensor_tensor(void* self, void* other) { void* ret = _lantern_logical_and_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_and_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_and_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_and_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_and__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_and__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_and__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_and_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_logical_and_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_logical_and_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_or_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_logical_or_tensor_tensor(void* self, void* other) { void* ret = _lantern_logical_or_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_or_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_or_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_or_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logical_or__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_logical_or__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_logical_or__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logical_or_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_logical_or_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_logical_or_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_blackman_window_intt_tensoroptions)(void* window_length, void* options);
  HOST_API void* lantern_blackman_window_intt_tensoroptions(void* window_length, void* options) { void* ret = _lantern_blackman_window_intt_tensoroptions(window_length, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_blackman_window_intt_bool_tensoroptions)(void* window_length, void* periodic, void* options);
  HOST_API void* lantern_blackman_window_intt_bool_tensoroptions(void* window_length, void* periodic, void* options) { void* ret = _lantern_blackman_window_intt_bool_tensoroptions(window_length, periodic, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bmm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_bmm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_bmm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bmm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_Tensor_bmm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_Tensor_bmm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bmm_out_tensor_tensor_tensor)(void* out, void* self, void* mat2);
  HOST_API void* lantern_bmm_out_tensor_tensor_tensor(void* out, void* self, void* mat2) { void* ret = _lantern_bmm_out_tensor_tensor_tensor(out, self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_broadcast_tensors_tensorlist)(void* tensors);
  HOST_API void* lantern_broadcast_tensors_tensorlist(void* tensors) { void* ret = _lantern_broadcast_tensors_tensorlist(tensors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cat_tensorlist_intt)(void* tensors, void* dim);
  HOST_API void* lantern_cat_tensorlist_intt(void* tensors, void* dim) { void* ret = _lantern_cat_tensorlist_intt(tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cat_out_tensor_tensorlist_intt)(void* out, void* tensors, void* dim);
  HOST_API void* lantern_cat_out_tensor_tensorlist_intt(void* out, void* tensors, void* dim) { void* ret = _lantern_cat_out_tensor_tensorlist_intt(out, tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cat_tensorlist_dimname)(void* tensors, void* dim);
  HOST_API void* lantern_cat_tensorlist_dimname(void* tensors, void* dim) { void* ret = _lantern_cat_tensorlist_dimname(tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cat_out_tensor_tensorlist_dimname)(void* out, void* tensors, void* dim);
  HOST_API void* lantern_cat_out_tensor_tensorlist_dimname(void* out, void* tensors, void* dim) { void* ret = _lantern_cat_out_tensor_tensorlist_dimname(out, tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ceil_tensor)(void* self);
  HOST_API void* lantern_ceil_tensor(void* self) { void* ret = _lantern_ceil_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ceil_tensor)(void* self);
  HOST_API void* lantern_Tensor_ceil_tensor(void* self) { void* ret = _lantern_Tensor_ceil_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ceil__tensor)(void* self);
  HOST_API void* lantern_ceil__tensor(void* self) { void* ret = _lantern_ceil__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ceil__tensor)(void* self);
  HOST_API void* lantern_Tensor_ceil__tensor(void* self) { void* ret = _lantern_Tensor_ceil__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ceil_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_ceil_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_ceil_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_chain_matmul_tensorlist)(void* matrices);
  HOST_API void* lantern_chain_matmul_tensorlist(void* matrices) { void* ret = _lantern_chain_matmul_tensorlist(matrices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_chunk_tensor_intt_intt)(void* self, void* chunks, void* dim);
  HOST_API void* lantern_chunk_tensor_intt_intt(void* self, void* chunks, void* dim) { void* ret = _lantern_chunk_tensor_intt_intt(self, chunks, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_chunk_tensor_intt_intt)(void* self, void* chunks, void* dim);
  HOST_API void* lantern_Tensor_chunk_tensor_intt_intt(void* self, void* chunks, void* dim) { void* ret = _lantern_Tensor_chunk_tensor_intt_intt(self, chunks, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_tensor_scalar_scalar)(void* self, void* min, void* max);
  HOST_API void* lantern_clamp_tensor_scalar_scalar(void* self, void* min, void* max) { void* ret = _lantern_clamp_tensor_scalar_scalar(self, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp_tensor_scalar_scalar)(void* self, void* min, void* max);
  HOST_API void* lantern_Tensor_clamp_tensor_scalar_scalar(void* self, void* min, void* max) { void* ret = _lantern_Tensor_clamp_tensor_scalar_scalar(self, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp__tensor_scalar_scalar)(void* self, void* min, void* max);
  HOST_API void* lantern_clamp__tensor_scalar_scalar(void* self, void* min, void* max) { void* ret = _lantern_clamp__tensor_scalar_scalar(self, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp__tensor_scalar_scalar)(void* self, void* min, void* max);
  HOST_API void* lantern_Tensor_clamp__tensor_scalar_scalar(void* self, void* min, void* max) { void* ret = _lantern_Tensor_clamp__tensor_scalar_scalar(self, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_out_tensor_tensor_scalar_scalar)(void* out, void* self, void* min, void* max);
  HOST_API void* lantern_clamp_out_tensor_tensor_scalar_scalar(void* out, void* self, void* min, void* max) { void* ret = _lantern_clamp_out_tensor_tensor_scalar_scalar(out, self, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_max_tensor_scalar)(void* self, void* max);
  HOST_API void* lantern_clamp_max_tensor_scalar(void* self, void* max) { void* ret = _lantern_clamp_max_tensor_scalar(self, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp_max_tensor_scalar)(void* self, void* max);
  HOST_API void* lantern_Tensor_clamp_max_tensor_scalar(void* self, void* max) { void* ret = _lantern_Tensor_clamp_max_tensor_scalar(self, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_max__tensor_scalar)(void* self, void* max);
  HOST_API void* lantern_clamp_max__tensor_scalar(void* self, void* max) { void* ret = _lantern_clamp_max__tensor_scalar(self, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp_max__tensor_scalar)(void* self, void* max);
  HOST_API void* lantern_Tensor_clamp_max__tensor_scalar(void* self, void* max) { void* ret = _lantern_Tensor_clamp_max__tensor_scalar(self, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_max_out_tensor_tensor_scalar)(void* out, void* self, void* max);
  HOST_API void* lantern_clamp_max_out_tensor_tensor_scalar(void* out, void* self, void* max) { void* ret = _lantern_clamp_max_out_tensor_tensor_scalar(out, self, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_min_tensor_scalar)(void* self, void* min);
  HOST_API void* lantern_clamp_min_tensor_scalar(void* self, void* min) { void* ret = _lantern_clamp_min_tensor_scalar(self, min); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp_min_tensor_scalar)(void* self, void* min);
  HOST_API void* lantern_Tensor_clamp_min_tensor_scalar(void* self, void* min) { void* ret = _lantern_Tensor_clamp_min_tensor_scalar(self, min); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_min__tensor_scalar)(void* self, void* min);
  HOST_API void* lantern_clamp_min__tensor_scalar(void* self, void* min) { void* ret = _lantern_clamp_min__tensor_scalar(self, min); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clamp_min__tensor_scalar)(void* self, void* min);
  HOST_API void* lantern_Tensor_clamp_min__tensor_scalar(void* self, void* min) { void* ret = _lantern_Tensor_clamp_min__tensor_scalar(self, min); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clamp_min_out_tensor_tensor_scalar)(void* out, void* self, void* min);
  HOST_API void* lantern_clamp_min_out_tensor_tensor_scalar(void* out, void* self, void* min) { void* ret = _lantern_clamp_min_out_tensor_tensor_scalar(out, self, min); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_is_acceptable_tensor)(void* self);
  HOST_API void* lantern_cudnn_is_acceptable_tensor(void* self) { void* ret = _lantern_cudnn_is_acceptable_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_constant_pad_nd_tensor_intarrayref_scalar)(void* self, void* pad, void* value);
  HOST_API void* lantern_constant_pad_nd_tensor_intarrayref_scalar(void* self, void* pad, void* value) { void* ret = _lantern_constant_pad_nd_tensor_intarrayref_scalar(self, pad, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_contiguous_tensor_memoryformat)(void* self, void* memory_format);
  HOST_API void* lantern_Tensor_contiguous_tensor_memoryformat(void* self, void* memory_format) { void* ret = _lantern_Tensor_contiguous_tensor_memoryformat(self, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups);
  HOST_API void* lantern_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups) { void* ret = _lantern_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt(input, weight, bias, stride, padding, dilation, transposed, output_padding, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_convolution_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups);
  HOST_API void* lantern_convolution_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups) { void* ret = _lantern_convolution_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt(input, weight, bias, stride, padding, dilation, transposed, output_padding, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_convolution_backward_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_stdarraybool)(void* grad_output, void* input, void* weight, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* output_mask);
  HOST_API void* lantern_convolution_backward_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_stdarraybool(void* grad_output, void* input, void* weight, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* output_mask) { void* ret = _lantern_convolution_backward_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_stdarraybool(grad_output, input, weight, stride, padding, dilation, transposed, output_padding, groups, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* benchmark, void* deterministic, void* cudnn_enabled);
  HOST_API void* lantern__convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* benchmark, void* deterministic, void* cudnn_enabled) { void* ret = _lantern__convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool(input, weight, bias, stride, padding, dilation, transposed, output_padding, groups, benchmark, deterministic, cudnn_enabled); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__convolution_nogroup_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding);
  HOST_API void* lantern__convolution_nogroup_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* transposed, void* output_padding) { void* ret = _lantern__convolution_nogroup_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref(input, weight, bias, stride, padding, dilation, transposed, output_padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__convolution_double_backward_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool_stdarraybool)(void* ggI, void* ggW, void* ggb, void* gO, void* weight, void* self, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* benchmark, void* deterministic, void* cudnn_enabled, void* output_mask);
  HOST_API void* lantern__convolution_double_backward_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool_stdarraybool(void* ggI, void* ggW, void* ggb, void* gO, void* weight, void* self, void* stride, void* padding, void* dilation, void* transposed, void* output_padding, void* groups, void* benchmark, void* deterministic, void* cudnn_enabled, void* output_mask) { void* ret = _lantern__convolution_double_backward_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool_stdarraybool(ggI, ggW, ggb, gO, weight, self, stride, padding, dilation, transposed, output_padding, groups, benchmark, deterministic, cudnn_enabled, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups);
  HOST_API void* lantern_conv1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups) { void* ret = _lantern_conv1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(input, weight, bias, stride, padding, dilation, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups);
  HOST_API void* lantern_conv2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups) { void* ret = _lantern_conv2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(input, weight, bias, stride, padding, dilation, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups);
  HOST_API void* lantern_conv3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(void* input, void* weight, void* bias, void* stride, void* padding, void* dilation, void* groups) { void* ret = _lantern_conv3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(input, weight, bias, stride, padding, dilation, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv_tbc_tensor_tensor_tensor_intt)(void* self, void* weight, void* bias, void* pad);
  HOST_API void* lantern_conv_tbc_tensor_tensor_tensor_intt(void* self, void* weight, void* bias, void* pad) { void* ret = _lantern_conv_tbc_tensor_tensor_tensor_intt(self, weight, bias, pad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv_tbc_backward_tensor_tensor_tensor_tensor_intt)(void* self, void* input, void* weight, void* bias, void* pad);
  HOST_API void* lantern_conv_tbc_backward_tensor_tensor_tensor_tensor_intt(void* self, void* input, void* weight, void* bias, void* pad) { void* ret = _lantern_conv_tbc_backward_tensor_tensor_tensor_tensor_intt(self, input, weight, bias, pad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv_transpose1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation);
  HOST_API void* lantern_conv_transpose1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation) { void* ret = _lantern_conv_transpose1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(input, weight, bias, stride, padding, output_padding, groups, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv_transpose2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation);
  HOST_API void* lantern_conv_transpose2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation) { void* ret = _lantern_conv_transpose2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(input, weight, bias, stride, padding, output_padding, groups, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_conv_transpose3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation);
  HOST_API void* lantern_conv_transpose3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(void* input, void* weight, void* bias, void* stride, void* padding, void* output_padding, void* groups, void* dilation) { void* ret = _lantern_conv_transpose3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref(input, weight, bias, stride, padding, output_padding, groups, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_copy__tensor_tensor_bool)(void* self, void* src, void* non_blocking);
  HOST_API void* lantern_Tensor_copy__tensor_tensor_bool(void* self, void* src, void* non_blocking) { void* ret = _lantern_Tensor_copy__tensor_tensor_bool(self, src, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__copy_from_tensor_tensor_bool)(void* self, void* dst, void* non_blocking);
  HOST_API void* lantern__copy_from_tensor_tensor_bool(void* self, void* dst, void* non_blocking) { void* ret = _lantern__copy_from_tensor_tensor_bool(self, dst, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cos_tensor)(void* self);
  HOST_API void* lantern_cos_tensor(void* self) { void* ret = _lantern_cos_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cos_tensor)(void* self);
  HOST_API void* lantern_Tensor_cos_tensor(void* self) { void* ret = _lantern_Tensor_cos_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cos__tensor)(void* self);
  HOST_API void* lantern_cos__tensor(void* self) { void* ret = _lantern_cos__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cos__tensor)(void* self);
  HOST_API void* lantern_Tensor_cos__tensor(void* self) { void* ret = _lantern_Tensor_cos__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cos_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_cos_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_cos_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cosh_tensor)(void* self);
  HOST_API void* lantern_cosh_tensor(void* self) { void* ret = _lantern_cosh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cosh_tensor)(void* self);
  HOST_API void* lantern_Tensor_cosh_tensor(void* self) { void* ret = _lantern_Tensor_cosh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cosh__tensor)(void* self);
  HOST_API void* lantern_cosh__tensor(void* self) { void* ret = _lantern_cosh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cosh__tensor)(void* self);
  HOST_API void* lantern_Tensor_cosh__tensor(void* self) { void* ret = _lantern_Tensor_cosh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cosh_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_cosh_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_cosh_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cosine_embedding_loss_tensor_tensor_tensor_double_intt)(void* input1, void* input2, void* target, void* margin, void* reduction);
  HOST_API void* lantern_cosine_embedding_loss_tensor_tensor_tensor_double_intt(void* input1, void* input2, void* target, void* margin, void* reduction) { void* ret = _lantern_cosine_embedding_loss_tensor_tensor_tensor_double_intt(input1, input2, target, margin, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_affine_grid_generator_tensor_intt_intt_intt_intt)(void* theta, void* N, void* C, void* H, void* W);
  HOST_API void* lantern_cudnn_affine_grid_generator_tensor_intt_intt_intt_intt(void* theta, void* N, void* C, void* H, void* W) { void* ret = _lantern_cudnn_affine_grid_generator_tensor_intt_intt_intt_intt(theta, N, C, H, W); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_affine_grid_generator_backward_tensor_intt_intt_intt_intt)(void* grad, void* N, void* C, void* H, void* W);
  HOST_API void* lantern_cudnn_affine_grid_generator_backward_tensor_intt_intt_intt_intt(void* grad, void* N, void* C, void* H, void* W) { void* ret = _lantern_cudnn_affine_grid_generator_backward_tensor_intt_intt_intt_intt(grad, N, C, H, W); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* exponential_average_factor, void* epsilon);
  HOST_API void* lantern_cudnn_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* exponential_average_factor, void* epsilon) { void* ret = _lantern_cudnn_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(input, weight, bias, running_mean, running_var, training, exponential_average_factor, epsilon); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double_tensor)(void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var, void* epsilon, void* reserveSpace);
  HOST_API void* lantern_cudnn_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double_tensor(void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var, void* epsilon, void* reserveSpace) { void* ret = _lantern_cudnn_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double_tensor(input, grad_output, weight, running_mean, running_var, save_mean, save_var, epsilon, reserveSpace); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self_size, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask);
  HOST_API void* lantern_cudnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask) { void* ret = _lantern_cudnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(self, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(weight_size, grad_output, self, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* bias, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* bias, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, bias, padding, output_padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_transpose_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_transpose_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_transpose_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, padding, output_padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask);
  HOST_API void* lantern_cudnn_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask) { void* ret = _lantern_cudnn_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(self, grad_output, weight, padding, output_padding, stride, dilation, groups, benchmark, deterministic, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_cudnn_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_cudnn_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(weight_size, grad_output, self, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_grid_sampler_tensor_tensor)(void* self, void* grid);
  HOST_API void* lantern_cudnn_grid_sampler_tensor_tensor(void* self, void* grid) { void* ret = _lantern_cudnn_grid_sampler_tensor_tensor(self, grid); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cudnn_grid_sampler_backward_tensor_tensor_tensor)(void* self, void* grid, void* grad_output);
  HOST_API void* lantern_cudnn_grid_sampler_backward_tensor_tensor_tensor(void* self, void* grid, void* grad_output) { void* ret = _lantern_cudnn_grid_sampler_backward_tensor_tensor_tensor(self, grid, grad_output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummax_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_cummax_tensor_intt(void* self, void* dim) { void* ret = _lantern_cummax_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cummax_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_cummax_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_cummax_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummax_out_tensor_tensor_tensor_intt)(void* values, void* indices, void* self, void* dim);
  HOST_API void* lantern_cummax_out_tensor_tensor_tensor_intt(void* values, void* indices, void* self, void* dim) { void* ret = _lantern_cummax_out_tensor_tensor_tensor_intt(values, indices, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummax_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_cummax_tensor_dimname(void* self, void* dim) { void* ret = _lantern_cummax_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cummax_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_cummax_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_cummax_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummax_out_tensor_tensor_tensor_dimname)(void* values, void* indices, void* self, void* dim);
  HOST_API void* lantern_cummax_out_tensor_tensor_tensor_dimname(void* values, void* indices, void* self, void* dim) { void* ret = _lantern_cummax_out_tensor_tensor_tensor_dimname(values, indices, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cummax_helper_tensor_tensor_tensor_intt)(void* self, void* values, void* indices, void* dim);
  HOST_API void* lantern__cummax_helper_tensor_tensor_tensor_intt(void* self, void* values, void* indices, void* dim) { void* ret = _lantern__cummax_helper_tensor_tensor_tensor_intt(self, values, indices, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummin_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_cummin_tensor_intt(void* self, void* dim) { void* ret = _lantern_cummin_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cummin_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_cummin_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_cummin_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummin_out_tensor_tensor_tensor_intt)(void* values, void* indices, void* self, void* dim);
  HOST_API void* lantern_cummin_out_tensor_tensor_tensor_intt(void* values, void* indices, void* self, void* dim) { void* ret = _lantern_cummin_out_tensor_tensor_tensor_intt(values, indices, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummin_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_cummin_tensor_dimname(void* self, void* dim) { void* ret = _lantern_cummin_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cummin_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_cummin_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_cummin_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cummin_out_tensor_tensor_tensor_dimname)(void* values, void* indices, void* self, void* dim);
  HOST_API void* lantern_cummin_out_tensor_tensor_tensor_dimname(void* values, void* indices, void* self, void* dim) { void* ret = _lantern_cummin_out_tensor_tensor_tensor_dimname(values, indices, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cummin_helper_tensor_tensor_tensor_intt)(void* self, void* values, void* indices, void* dim);
  HOST_API void* lantern__cummin_helper_tensor_tensor_tensor_intt(void* self, void* values, void* indices, void* dim) { void* ret = _lantern__cummin_helper_tensor_tensor_tensor_intt(self, values, indices, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumprod_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumprod_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_cumprod_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cumprod_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_cumprod_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_cumprod_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumprod_out_tensor_tensor_intt_scalartype)(void* out, void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumprod_out_tensor_tensor_intt_scalartype(void* out, void* self, void* dim, void* dtype) { void* ret = _lantern_cumprod_out_tensor_tensor_intt_scalartype(out, self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumprod_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumprod_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_cumprod_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cumprod_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_cumprod_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_cumprod_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumprod_out_tensor_tensor_dimname_scalartype)(void* out, void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumprod_out_tensor_tensor_dimname_scalartype(void* out, void* self, void* dim, void* dtype) { void* ret = _lantern_cumprod_out_tensor_tensor_dimname_scalartype(out, self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumsum_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumsum_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_cumsum_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cumsum_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_cumsum_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_cumsum_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumsum_out_tensor_tensor_intt_scalartype)(void* out, void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumsum_out_tensor_tensor_intt_scalartype(void* out, void* self, void* dim, void* dtype) { void* ret = _lantern_cumsum_out_tensor_tensor_intt_scalartype(out, self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumsum_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumsum_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_cumsum_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cumsum_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_cumsum_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_cumsum_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cumsum_out_tensor_tensor_dimname_scalartype)(void* out, void* self, void* dim, void* dtype);
  HOST_API void* lantern_cumsum_out_tensor_tensor_dimname_scalartype(void* out, void* self, void* dim, void* dtype) { void* ret = _lantern_cumsum_out_tensor_tensor_dimname_scalartype(out, self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_intt_bool)(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* reduction, void* zero_infinity);
  HOST_API void* lantern_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_intt_bool(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* reduction, void* zero_infinity) { void* ret = _lantern_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_intt_bool(log_probs, targets, input_lengths, target_lengths, blank, reduction, zero_infinity); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ctc_loss_tensor_tensor_tensor_tensor_intt_intt_bool)(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* reduction, void* zero_infinity);
  HOST_API void* lantern_ctc_loss_tensor_tensor_tensor_tensor_intt_intt_bool(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* reduction, void* zero_infinity) { void* ret = _lantern_ctc_loss_tensor_tensor_tensor_tensor_intt_intt_bool(log_probs, targets, input_lengths, target_lengths, blank, reduction, zero_infinity); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool)(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* zero_infinity);
  HOST_API void* lantern__ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool(void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* blank, void* zero_infinity) { void* ret = _lantern__ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool(log_probs, targets, input_lengths, target_lengths, blank, zero_infinity); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__ctc_loss_backward_tensor_tensor_tensor_intarrayref_intarrayref_tensor_tensor_intt_bool)(void* grad, void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* neg_log_likelihood, void* log_alpha, void* blank, void* zero_infinity);
  HOST_API void* lantern__ctc_loss_backward_tensor_tensor_tensor_intarrayref_intarrayref_tensor_tensor_intt_bool(void* grad, void* log_probs, void* targets, void* input_lengths, void* target_lengths, void* neg_log_likelihood, void* log_alpha, void* blank, void* zero_infinity) { void* ret = _lantern__ctc_loss_backward_tensor_tensor_tensor_intarrayref_intarrayref_tensor_tensor_intt_bool(grad, log_probs, targets, input_lengths, target_lengths, neg_log_likelihood, log_alpha, blank, zero_infinity); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_det_tensor)(void* self);
  HOST_API void* lantern_det_tensor(void* self) { void* ret = _lantern_det_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_det_tensor)(void* self);
  HOST_API void* lantern_Tensor_det_tensor(void* self) { void* ret = _lantern_Tensor_det_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diag_embed_tensor_intt_intt_intt)(void* self, void* offset, void* dim1, void* dim2);
  HOST_API void* lantern_diag_embed_tensor_intt_intt_intt(void* self, void* offset, void* dim1, void* dim2) { void* ret = _lantern_diag_embed_tensor_intt_intt_intt(self, offset, dim1, dim2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_diag_embed_tensor_intt_intt_intt)(void* self, void* offset, void* dim1, void* dim2);
  HOST_API void* lantern_Tensor_diag_embed_tensor_intt_intt_intt(void* self, void* offset, void* dim1, void* dim2) { void* ret = _lantern_Tensor_diag_embed_tensor_intt_intt_intt(self, offset, dim1, dim2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diagflat_tensor_intt)(void* self, void* offset);
  HOST_API void* lantern_diagflat_tensor_intt(void* self, void* offset) { void* ret = _lantern_diagflat_tensor_intt(self, offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_diagflat_tensor_intt)(void* self, void* offset);
  HOST_API void* lantern_Tensor_diagflat_tensor_intt(void* self, void* offset) { void* ret = _lantern_Tensor_diagflat_tensor_intt(self, offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diagonal_tensor_intt_intt_intt)(void* self, void* offset, void* dim1, void* dim2);
  HOST_API void* lantern_diagonal_tensor_intt_intt_intt(void* self, void* offset, void* dim1, void* dim2) { void* ret = _lantern_diagonal_tensor_intt_intt_intt(self, offset, dim1, dim2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_diagonal_tensor_intt_intt_intt)(void* self, void* offset, void* dim1, void* dim2);
  HOST_API void* lantern_Tensor_diagonal_tensor_intt_intt_intt(void* self, void* offset, void* dim1, void* dim2) { void* ret = _lantern_Tensor_diagonal_tensor_intt_intt_intt(self, offset, dim1, dim2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diagonal_tensor_dimname_dimname_dimname_intt)(void* self, void* outdim, void* dim1, void* dim2, void* offset);
  HOST_API void* lantern_diagonal_tensor_dimname_dimname_dimname_intt(void* self, void* outdim, void* dim1, void* dim2, void* offset) { void* ret = _lantern_diagonal_tensor_dimname_dimname_dimname_intt(self, outdim, dim1, dim2, offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_diagonal_tensor_dimname_dimname_dimname_intt)(void* self, void* outdim, void* dim1, void* dim2, void* offset);
  HOST_API void* lantern_Tensor_diagonal_tensor_dimname_dimname_dimname_intt(void* self, void* outdim, void* dim1, void* dim2, void* offset) { void* ret = _lantern_Tensor_diagonal_tensor_dimname_dimname_dimname_intt(self, outdim, dim1, dim2, offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fill_diagonal__tensor_scalar_bool)(void* self, void* fill_value, void* wrap);
  HOST_API void* lantern_Tensor_fill_diagonal__tensor_scalar_bool(void* self, void* fill_value, void* wrap) { void* ret = _lantern_Tensor_fill_diagonal__tensor_scalar_bool(self, fill_value, wrap); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_div_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_div_tensor_tensor(void* self, void* other) { void* ret = _lantern_div_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_div_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_div_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_div_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_div__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_div__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_div__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_div_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_div_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_div_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_div_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_div_tensor_scalar(void* self, void* other) { void* ret = _lantern_div_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_div_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_div_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_div_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_div__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_div__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_div__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dot_tensor_tensor)(void* self, void* tensor);
  HOST_API void* lantern_dot_tensor_tensor(void* self, void* tensor) { void* ret = _lantern_dot_tensor_tensor(self, tensor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_dot_tensor_tensor)(void* self, void* tensor);
  HOST_API void* lantern_Tensor_dot_tensor_tensor(void* self, void* tensor) { void* ret = _lantern_Tensor_dot_tensor_tensor(self, tensor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dot_out_tensor_tensor_tensor)(void* out, void* self, void* tensor);
  HOST_API void* lantern_dot_out_tensor_tensor_tensor(void* out, void* self, void* tensor) { void* ret = _lantern_dot_out_tensor_tensor_tensor(out, self, tensor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_einsum_stdstring_tensorlist)(void* equation, void* tensors);
  HOST_API void* lantern_einsum_stdstring_tensorlist(void* equation, void* tensors) { void* ret = _lantern_einsum_stdstring_tensorlist(equation, tensors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_tensor_tensor_intt_bool_bool)(void* weight, void* indices, void* padding_idx, void* scale_grad_by_freq, void* sparse);
  HOST_API void* lantern_embedding_tensor_tensor_intt_bool_bool(void* weight, void* indices, void* padding_idx, void* scale_grad_by_freq, void* sparse) { void* ret = _lantern_embedding_tensor_tensor_intt_bool_bool(weight, indices, padding_idx, scale_grad_by_freq, sparse); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_backward_tensor_tensor_intt_intt_bool_bool)(void* grad, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq, void* sparse);
  HOST_API void* lantern_embedding_backward_tensor_tensor_intt_intt_bool_bool(void* grad, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq, void* sparse) { void* ret = _lantern_embedding_backward_tensor_tensor_intt_intt_bool_bool(grad, indices, num_weights, padding_idx, scale_grad_by_freq, sparse); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_dense_backward_tensor_tensor_intt_intt_bool)(void* grad_output, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq);
  HOST_API void* lantern_embedding_dense_backward_tensor_tensor_intt_intt_bool(void* grad_output, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq) { void* ret = _lantern_embedding_dense_backward_tensor_tensor_intt_intt_bool(grad_output, indices, num_weights, padding_idx, scale_grad_by_freq); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_renorm__tensor_tensor_double_double)(void* self, void* indices, void* max_norm, void* norm_type);
  HOST_API void* lantern_embedding_renorm__tensor_tensor_double_double(void* self, void* indices, void* max_norm, void* norm_type) { void* ret = _lantern_embedding_renorm__tensor_tensor_double_double(self, indices, max_norm, norm_type); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_sparse_backward_tensor_tensor_intt_intt_bool)(void* grad, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq);
  HOST_API void* lantern_embedding_sparse_backward_tensor_tensor_intt_intt_bool(void* grad, void* indices, void* num_weights, void* padding_idx, void* scale_grad_by_freq) { void* ret = _lantern_embedding_sparse_backward_tensor_tensor_intt_intt_bool(grad, indices, num_weights, padding_idx, scale_grad_by_freq); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool)(void* weight, void* indices, void* offsets, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights, void* include_last_offset);
  HOST_API void* lantern_embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool(void* weight, void* indices, void* offsets, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights, void* include_last_offset) { void* ret = _lantern_embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool(weight, indices, offsets, scale_grad_by_freq, mode, sparse, per_sample_weights, include_last_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool)(void* weight, void* indices, void* offsets, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights, void* include_last_offset);
  HOST_API void* lantern__embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool(void* weight, void* indices, void* offsets, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights, void* include_last_offset) { void* ret = _lantern__embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool(weight, indices, offsets, scale_grad_by_freq, mode, sparse, per_sample_weights, include_last_offset); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__embedding_bag_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_bool_tensor)(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* maximum_indices, void* num_weights, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights);
  HOST_API void* lantern__embedding_bag_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_bool_tensor(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* maximum_indices, void* num_weights, void* scale_grad_by_freq, void* mode, void* sparse, void* per_sample_weights) { void* ret = _lantern__embedding_bag_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_bool_tensor(grad, indices, offsets, offset2bag, bag_size, maximum_indices, num_weights, scale_grad_by_freq, mode, sparse, per_sample_weights); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__embedding_bag_sparse_backward_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor)(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* num_weights, void* scale_grad_by_freq, void* mode, void* per_sample_weights);
  HOST_API void* lantern__embedding_bag_sparse_backward_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* num_weights, void* scale_grad_by_freq, void* mode, void* per_sample_weights) { void* ret = _lantern__embedding_bag_sparse_backward_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor(grad, indices, offsets, offset2bag, bag_size, num_weights, scale_grad_by_freq, mode, per_sample_weights); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__embedding_bag_dense_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor)(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* maximum_indices, void* num_weights, void* scale_grad_by_freq, void* mode, void* per_sample_weights);
  HOST_API void* lantern__embedding_bag_dense_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor(void* grad, void* indices, void* offsets, void* offset2bag, void* bag_size, void* maximum_indices, void* num_weights, void* scale_grad_by_freq, void* mode, void* per_sample_weights) { void* ret = _lantern__embedding_bag_dense_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor(grad, indices, offsets, offset2bag, bag_size, maximum_indices, num_weights, scale_grad_by_freq, mode, per_sample_weights); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__embedding_bag_per_sample_weights_backward_tensor_tensor_tensor_tensor_tensor_intt)(void* grad, void* weight, void* indices, void* offsets, void* offset2bag, void* mode);
  HOST_API void* lantern__embedding_bag_per_sample_weights_backward_tensor_tensor_tensor_tensor_tensor_intt(void* grad, void* weight, void* indices, void* offsets, void* offset2bag, void* mode) { void* ret = _lantern__embedding_bag_per_sample_weights_backward_tensor_tensor_tensor_tensor_tensor_intt(grad, weight, indices, offsets, offset2bag, mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_empty_intarrayref_dimnamelist_tensoroptions_memoryformat)(void* size, void* names, void* options, void* memory_format);
  HOST_API void* lantern_empty_intarrayref_dimnamelist_tensoroptions_memoryformat(void* size, void* names, void* options, void* memory_format) { void* ret = _lantern_empty_intarrayref_dimnamelist_tensoroptions_memoryformat(size, names, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_empty_intarrayref_tensoroptions_memoryformat)(void* size, void* options, void* memory_format);
  HOST_API void* lantern_empty_intarrayref_tensoroptions_memoryformat(void* size, void* options, void* memory_format) { void* ret = _lantern_empty_intarrayref_tensoroptions_memoryformat(size, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_new_empty_tensor_intarrayref_tensoroptions)(void* self, void* size, void* options);
  HOST_API void* lantern_Tensor_new_empty_tensor_intarrayref_tensoroptions(void* self, void* size, void* options) { void* ret = _lantern_Tensor_new_empty_tensor_intarrayref_tensoroptions(self, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_new_full_tensor_intarrayref_scalar_tensoroptions)(void* self, void* size, void* fill_value, void* options);
  HOST_API void* lantern_Tensor_new_full_tensor_intarrayref_scalar_tensoroptions(void* self, void* size, void* fill_value, void* options) { void* ret = _lantern_Tensor_new_full_tensor_intarrayref_scalar_tensoroptions(self, size, fill_value, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_new_zeros_tensor_intarrayref_tensoroptions)(void* self, void* size, void* options);
  HOST_API void* lantern_Tensor_new_zeros_tensor_intarrayref_tensoroptions(void* self, void* size, void* options) { void* ret = _lantern_Tensor_new_zeros_tensor_intarrayref_tensoroptions(self, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__empty_affine_quantized_intarrayref_tensoroptions_double_intt_memoryformat)(void* size, void* options, void* scale, void* zero_point, void* memory_format);
  HOST_API void* lantern__empty_affine_quantized_intarrayref_tensoroptions_double_intt_memoryformat(void* size, void* options, void* scale, void* zero_point, void* memory_format) { void* ret = _lantern__empty_affine_quantized_intarrayref_tensoroptions_double_intt_memoryformat(size, options, scale, zero_point, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__empty_per_channel_affine_quantized_intarrayref_tensor_tensor_intt_tensoroptions_memoryformat)(void* size, void* scales, void* zero_points, void* axis, void* options, void* memory_format);
  HOST_API void* lantern__empty_per_channel_affine_quantized_intarrayref_tensor_tensor_intt_tensoroptions_memoryformat(void* size, void* scales, void* zero_points, void* axis, void* options, void* memory_format) { void* ret = _lantern__empty_per_channel_affine_quantized_intarrayref_tensor_tensor_intt_tensoroptions_memoryformat(size, scales, zero_points, axis, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_resize__tensor_intarrayref_memoryformat)(void* self, void* size, void* memory_format);
  HOST_API void* lantern_Tensor_resize__tensor_intarrayref_memoryformat(void* self, void* size, void* memory_format) { void* ret = _lantern_Tensor_resize__tensor_intarrayref_memoryformat(self, size, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_empty_out_tensor_intarrayref_memoryformat)(void* out, void* size, void* memory_format);
  HOST_API void* lantern_empty_out_tensor_intarrayref_memoryformat(void* out, void* size, void* memory_format) { void* ret = _lantern_empty_out_tensor_intarrayref_memoryformat(out, size, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_empty_like_tensor_tensoroptions_memoryformat)(void* self, void* options, void* memory_format);
  HOST_API void* lantern_empty_like_tensor_tensoroptions_memoryformat(void* self, void* options, void* memory_format) { void* ret = _lantern_empty_like_tensor_tensoroptions_memoryformat(self, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_empty_strided_intarrayref_intarrayref_tensoroptions)(void* size, void* stride, void* options);
  HOST_API void* lantern_empty_strided_intarrayref_intarrayref_tensoroptions(void* size, void* stride, void* options) { void* ret = _lantern_empty_strided_intarrayref_intarrayref_tensoroptions(size, stride, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erf_tensor)(void* self);
  HOST_API void* lantern_erf_tensor(void* self) { void* ret = _lantern_erf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erf_tensor)(void* self);
  HOST_API void* lantern_Tensor_erf_tensor(void* self) { void* ret = _lantern_Tensor_erf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erf__tensor)(void* self);
  HOST_API void* lantern_erf__tensor(void* self) { void* ret = _lantern_erf__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erf__tensor)(void* self);
  HOST_API void* lantern_Tensor_erf__tensor(void* self) { void* ret = _lantern_Tensor_erf__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erf_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_erf_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_erf_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erfc_tensor)(void* self);
  HOST_API void* lantern_erfc_tensor(void* self) { void* ret = _lantern_erfc_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erfc_tensor)(void* self);
  HOST_API void* lantern_Tensor_erfc_tensor(void* self) { void* ret = _lantern_Tensor_erfc_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erfc__tensor)(void* self);
  HOST_API void* lantern_erfc__tensor(void* self) { void* ret = _lantern_erfc__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erfc__tensor)(void* self);
  HOST_API void* lantern_Tensor_erfc__tensor(void* self) { void* ret = _lantern_Tensor_erfc__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erfc_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_erfc_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_erfc_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_exp_tensor)(void* self);
  HOST_API void* lantern_exp_tensor(void* self) { void* ret = _lantern_exp_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_exp_tensor)(void* self);
  HOST_API void* lantern_Tensor_exp_tensor(void* self) { void* ret = _lantern_Tensor_exp_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_exp__tensor)(void* self);
  HOST_API void* lantern_exp__tensor(void* self) { void* ret = _lantern_exp__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_exp__tensor)(void* self);
  HOST_API void* lantern_Tensor_exp__tensor(void* self) { void* ret = _lantern_Tensor_exp__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_exp_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_exp_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_exp_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_expm1_tensor)(void* self);
  HOST_API void* lantern_expm1_tensor(void* self) { void* ret = _lantern_expm1_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_expm1_tensor)(void* self);
  HOST_API void* lantern_Tensor_expm1_tensor(void* self) { void* ret = _lantern_Tensor_expm1_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_expm1__tensor)(void* self);
  HOST_API void* lantern_expm1__tensor(void* self) { void* ret = _lantern_expm1__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_expm1__tensor)(void* self);
  HOST_API void* lantern_Tensor_expm1__tensor(void* self) { void* ret = _lantern_Tensor_expm1__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_expm1_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_expm1_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_expm1_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_expand_tensor_intarrayref_bool)(void* self, void* size, void* implicit);
  HOST_API void* lantern_Tensor_expand_tensor_intarrayref_bool(void* self, void* size, void* implicit) { void* ret = _lantern_Tensor_expand_tensor_intarrayref_bool(self, size, implicit); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_expand_as_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_expand_as_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_expand_as_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eye_intt_tensoroptions)(void* n, void* options);
  HOST_API void* lantern_eye_intt_tensoroptions(void* n, void* options) { void* ret = _lantern_eye_intt_tensoroptions(n, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eye_intt_intt_tensoroptions)(void* n, void* m, void* options);
  HOST_API void* lantern_eye_intt_intt_tensoroptions(void* n, void* m, void* options) { void* ret = _lantern_eye_intt_intt_tensoroptions(n, m, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eye_out_tensor_intt)(void* out, void* n);
  HOST_API void* lantern_eye_out_tensor_intt(void* out, void* n) { void* ret = _lantern_eye_out_tensor_intt(out, n); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eye_out_tensor_intt_intt)(void* out, void* n, void* m);
  HOST_API void* lantern_eye_out_tensor_intt_intt(void* out, void* n, void* m) { void* ret = _lantern_eye_out_tensor_intt_intt(out, n, m); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_flatten_tensor_intt_intt)(void* self, void* start_dim, void* end_dim);
  HOST_API void* lantern_flatten_tensor_intt_intt(void* self, void* start_dim, void* end_dim) { void* ret = _lantern_flatten_tensor_intt_intt(self, start_dim, end_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_flatten_tensor_intt_intt)(void* self, void* start_dim, void* end_dim);
  HOST_API void* lantern_Tensor_flatten_tensor_intt_intt(void* self, void* start_dim, void* end_dim) { void* ret = _lantern_Tensor_flatten_tensor_intt_intt(self, start_dim, end_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_flatten_tensor_intt_intt_dimname)(void* self, void* start_dim, void* end_dim, void* out_dim);
  HOST_API void* lantern_flatten_tensor_intt_intt_dimname(void* self, void* start_dim, void* end_dim, void* out_dim) { void* ret = _lantern_flatten_tensor_intt_intt_dimname(self, start_dim, end_dim, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_flatten_tensor_intt_intt_dimname)(void* self, void* start_dim, void* end_dim, void* out_dim);
  HOST_API void* lantern_Tensor_flatten_tensor_intt_intt_dimname(void* self, void* start_dim, void* end_dim, void* out_dim) { void* ret = _lantern_Tensor_flatten_tensor_intt_intt_dimname(self, start_dim, end_dim, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_flatten_tensor_dimname_dimname_dimname)(void* self, void* start_dim, void* end_dim, void* out_dim);
  HOST_API void* lantern_flatten_tensor_dimname_dimname_dimname(void* self, void* start_dim, void* end_dim, void* out_dim) { void* ret = _lantern_flatten_tensor_dimname_dimname_dimname(self, start_dim, end_dim, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_flatten_tensor_dimname_dimname_dimname)(void* self, void* start_dim, void* end_dim, void* out_dim);
  HOST_API void* lantern_Tensor_flatten_tensor_dimname_dimname_dimname(void* self, void* start_dim, void* end_dim, void* out_dim) { void* ret = _lantern_Tensor_flatten_tensor_dimname_dimname_dimname(self, start_dim, end_dim, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_flatten_tensor_dimnamelist_dimname)(void* self, void* dims, void* out_dim);
  HOST_API void* lantern_flatten_tensor_dimnamelist_dimname(void* self, void* dims, void* out_dim) { void* ret = _lantern_flatten_tensor_dimnamelist_dimname(self, dims, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_flatten_tensor_dimnamelist_dimname)(void* self, void* dims, void* out_dim);
  HOST_API void* lantern_Tensor_flatten_tensor_dimnamelist_dimname(void* self, void* dims, void* out_dim) { void* ret = _lantern_Tensor_flatten_tensor_dimnamelist_dimname(self, dims, out_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fill__tensor_scalar)(void* self, void* value);
  HOST_API void* lantern_fill__tensor_scalar(void* self, void* value) { void* ret = _lantern_fill__tensor_scalar(self, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fill__tensor_scalar)(void* self, void* value);
  HOST_API void* lantern_Tensor_fill__tensor_scalar(void* self, void* value) { void* ret = _lantern_Tensor_fill__tensor_scalar(self, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fill__tensor_tensor)(void* self, void* value);
  HOST_API void* lantern_fill__tensor_tensor(void* self, void* value) { void* ret = _lantern_fill__tensor_tensor(self, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fill__tensor_tensor)(void* self, void* value);
  HOST_API void* lantern_Tensor_fill__tensor_tensor(void* self, void* value) { void* ret = _lantern_Tensor_fill__tensor_tensor(self, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor_tensor)(void* self);
  HOST_API void* lantern_floor_tensor(void* self) { void* ret = _lantern_floor_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor_tensor)(void* self);
  HOST_API void* lantern_Tensor_floor_tensor(void* self) { void* ret = _lantern_Tensor_floor_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor__tensor)(void* self);
  HOST_API void* lantern_floor__tensor(void* self) { void* ret = _lantern_floor__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor__tensor)(void* self);
  HOST_API void* lantern_Tensor_floor__tensor(void* self) { void* ret = _lantern_Tensor_floor__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_floor_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_floor_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor_divide_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_floor_divide_tensor_tensor(void* self, void* other) { void* ret = _lantern_floor_divide_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor_divide_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_floor_divide_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_floor_divide_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor_divide__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_floor_divide__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_floor_divide__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor_divide_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_floor_divide_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_floor_divide_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_floor_divide_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_floor_divide_tensor_scalar(void* self, void* other) { void* ret = _lantern_floor_divide_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor_divide_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_floor_divide_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_floor_divide_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_floor_divide__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_floor_divide__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_floor_divide__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frac_tensor)(void* self);
  HOST_API void* lantern_frac_tensor(void* self) { void* ret = _lantern_frac_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_frac_tensor)(void* self);
  HOST_API void* lantern_Tensor_frac_tensor(void* self) { void* ret = _lantern_Tensor_frac_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frac__tensor)(void* self);
  HOST_API void* lantern_frac__tensor(void* self) { void* ret = _lantern_frac__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_frac__tensor)(void* self);
  HOST_API void* lantern_Tensor_frac__tensor(void* self) { void* ret = _lantern_Tensor_frac__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frac_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_frac_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_frac_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_full_intarrayref_scalar_dimnamelist_tensoroptions)(void* size, void* fill_value, void* names, void* options);
  HOST_API void* lantern_full_intarrayref_scalar_dimnamelist_tensoroptions(void* size, void* fill_value, void* names, void* options) { void* ret = _lantern_full_intarrayref_scalar_dimnamelist_tensoroptions(size, fill_value, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_full_intarrayref_scalar_tensoroptions)(void* size, void* fill_value, void* options);
  HOST_API void* lantern_full_intarrayref_scalar_tensoroptions(void* size, void* fill_value, void* options) { void* ret = _lantern_full_intarrayref_scalar_tensoroptions(size, fill_value, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_full_out_tensor_intarrayref_scalar)(void* out, void* size, void* fill_value);
  HOST_API void* lantern_full_out_tensor_intarrayref_scalar(void* out, void* size, void* fill_value) { void* ret = _lantern_full_out_tensor_intarrayref_scalar(out, size, fill_value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_full_like_tensor_scalar_tensoroptions_memoryformat)(void* self, void* fill_value, void* options, void* memory_format);
  HOST_API void* lantern_full_like_tensor_scalar_tensoroptions_memoryformat(void* self, void* fill_value, void* options, void* memory_format) { void* ret = _lantern_full_like_tensor_scalar_tensoroptions_memoryformat(self, fill_value, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_from_file_stdstring_bool_intt_tensoroptions)(void* filename, void* shared, void* size, void* options);
  HOST_API void* lantern_from_file_stdstring_bool_intt_tensoroptions(void* filename, void* shared, void* size, void* options) { void* ret = _lantern_from_file_stdstring_bool_intt_tensoroptions(filename, shared, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_grid_sampler_tensor_tensor_intt_intt_bool)(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners);
  HOST_API void* lantern_grid_sampler_tensor_tensor_intt_intt_bool(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners) { void* ret = _lantern_grid_sampler_tensor_tensor_intt_intt_bool(input, grid, interpolation_mode, padding_mode, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_grid_sampler_2d_tensor_tensor_intt_intt_bool)(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners);
  HOST_API void* lantern_grid_sampler_2d_tensor_tensor_intt_intt_bool(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners) { void* ret = _lantern_grid_sampler_2d_tensor_tensor_intt_intt_bool(input, grid, interpolation_mode, padding_mode, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_grid_sampler_2d_backward_tensor_tensor_tensor_intt_intt_bool)(void* grad_output, void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners);
  HOST_API void* lantern_grid_sampler_2d_backward_tensor_tensor_tensor_intt_intt_bool(void* grad_output, void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners) { void* ret = _lantern_grid_sampler_2d_backward_tensor_tensor_tensor_intt_intt_bool(grad_output, input, grid, interpolation_mode, padding_mode, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_grid_sampler_3d_tensor_tensor_intt_intt_bool)(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners);
  HOST_API void* lantern_grid_sampler_3d_tensor_tensor_intt_intt_bool(void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners) { void* ret = _lantern_grid_sampler_3d_tensor_tensor_intt_intt_bool(input, grid, interpolation_mode, padding_mode, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_grid_sampler_3d_backward_tensor_tensor_tensor_intt_intt_bool)(void* grad_output, void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners);
  HOST_API void* lantern_grid_sampler_3d_backward_tensor_tensor_tensor_intt_intt_bool(void* grad_output, void* input, void* grid, void* interpolation_mode, void* padding_mode, void* align_corners) { void* ret = _lantern_grid_sampler_3d_backward_tensor_tensor_tensor_intt_intt_bool(grad_output, input, grid, interpolation_mode, padding_mode, align_corners); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hann_window_intt_tensoroptions)(void* window_length, void* options);
  HOST_API void* lantern_hann_window_intt_tensoroptions(void* window_length, void* options) { void* ret = _lantern_hann_window_intt_tensoroptions(window_length, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hann_window_intt_bool_tensoroptions)(void* window_length, void* periodic, void* options);
  HOST_API void* lantern_hann_window_intt_bool_tensoroptions(void* window_length, void* periodic, void* options) { void* ret = _lantern_hann_window_intt_bool_tensoroptions(window_length, periodic, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hamming_window_intt_tensoroptions)(void* window_length, void* options);
  HOST_API void* lantern_hamming_window_intt_tensoroptions(void* window_length, void* options) { void* ret = _lantern_hamming_window_intt_tensoroptions(window_length, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hamming_window_intt_bool_tensoroptions)(void* window_length, void* periodic, void* options);
  HOST_API void* lantern_hamming_window_intt_bool_tensoroptions(void* window_length, void* periodic, void* options) { void* ret = _lantern_hamming_window_intt_bool_tensoroptions(window_length, periodic, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hamming_window_intt_bool_double_tensoroptions)(void* window_length, void* periodic, void* alpha, void* options);
  HOST_API void* lantern_hamming_window_intt_bool_double_tensoroptions(void* window_length, void* periodic, void* alpha, void* options) { void* ret = _lantern_hamming_window_intt_bool_double_tensoroptions(window_length, periodic, alpha, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hamming_window_intt_bool_double_double_tensoroptions)(void* window_length, void* periodic, void* alpha, void* beta, void* options);
  HOST_API void* lantern_hamming_window_intt_bool_double_double_tensoroptions(void* window_length, void* periodic, void* alpha, void* beta, void* options) { void* ret = _lantern_hamming_window_intt_bool_double_double_tensoroptions(window_length, periodic, alpha, beta, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hinge_embedding_loss_tensor_tensor_double_intt)(void* self, void* target, void* margin, void* reduction);
  HOST_API void* lantern_hinge_embedding_loss_tensor_tensor_double_intt(void* self, void* target, void* margin, void* reduction) { void* ret = _lantern_hinge_embedding_loss_tensor_tensor_double_intt(self, target, margin, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ger_tensor_tensor)(void* self, void* vec2);
  HOST_API void* lantern_ger_tensor_tensor(void* self, void* vec2) { void* ret = _lantern_ger_tensor_tensor(self, vec2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ger_tensor_tensor)(void* self, void* vec2);
  HOST_API void* lantern_Tensor_ger_tensor_tensor(void* self, void* vec2) { void* ret = _lantern_Tensor_ger_tensor_tensor(self, vec2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ger_out_tensor_tensor_tensor)(void* out, void* self, void* vec2);
  HOST_API void* lantern_ger_out_tensor_tensor_tensor(void* out, void* self, void* vec2) { void* ret = _lantern_ger_out_tensor_tensor_tensor(out, self, vec2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_group_norm_tensor_intt_tensor_tensor_double_bool)(void* input, void* num_groups, void* weight, void* bias, void* eps, void* cudnn_enabled);
  HOST_API void* lantern_group_norm_tensor_intt_tensor_tensor_double_bool(void* input, void* num_groups, void* weight, void* bias, void* eps, void* cudnn_enabled) { void* ret = _lantern_group_norm_tensor_intt_tensor_tensor_double_bool(input, num_groups, weight, bias, eps, cudnn_enabled); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fft_tensor_intt_bool)(void* self, void* signal_ndim, void* normalized);
  HOST_API void* lantern_fft_tensor_intt_bool(void* self, void* signal_ndim, void* normalized) { void* ret = _lantern_fft_tensor_intt_bool(self, signal_ndim, normalized); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fft_tensor_intt_bool)(void* self, void* signal_ndim, void* normalized);
  HOST_API void* lantern_Tensor_fft_tensor_intt_bool(void* self, void* signal_ndim, void* normalized) { void* ret = _lantern_Tensor_fft_tensor_intt_bool(self, signal_ndim, normalized); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ifft_tensor_intt_bool)(void* self, void* signal_ndim, void* normalized);
  HOST_API void* lantern_ifft_tensor_intt_bool(void* self, void* signal_ndim, void* normalized) { void* ret = _lantern_ifft_tensor_intt_bool(self, signal_ndim, normalized); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ifft_tensor_intt_bool)(void* self, void* signal_ndim, void* normalized);
  HOST_API void* lantern_Tensor_ifft_tensor_intt_bool(void* self, void* signal_ndim, void* normalized) { void* ret = _lantern_Tensor_ifft_tensor_intt_bool(self, signal_ndim, normalized); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rfft_tensor_intt_bool_bool)(void* self, void* signal_ndim, void* normalized, void* onesided);
  HOST_API void* lantern_rfft_tensor_intt_bool_bool(void* self, void* signal_ndim, void* normalized, void* onesided) { void* ret = _lantern_rfft_tensor_intt_bool_bool(self, signal_ndim, normalized, onesided); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rfft_tensor_intt_bool_bool)(void* self, void* signal_ndim, void* normalized, void* onesided);
  HOST_API void* lantern_Tensor_rfft_tensor_intt_bool_bool(void* self, void* signal_ndim, void* normalized, void* onesided) { void* ret = _lantern_Tensor_rfft_tensor_intt_bool_bool(self, signal_ndim, normalized, onesided); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_irfft_tensor_intt_bool_bool_intarrayref)(void* self, void* signal_ndim, void* normalized, void* onesided, void* signal_sizes);
  HOST_API void* lantern_irfft_tensor_intt_bool_bool_intarrayref(void* self, void* signal_ndim, void* normalized, void* onesided, void* signal_sizes) { void* ret = _lantern_irfft_tensor_intt_bool_bool_intarrayref(self, signal_ndim, normalized, onesided, signal_sizes); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_irfft_tensor_intt_bool_bool_intarrayref)(void* self, void* signal_ndim, void* normalized, void* onesided, void* signal_sizes);
  HOST_API void* lantern_Tensor_irfft_tensor_intt_bool_bool_intarrayref(void* self, void* signal_ndim, void* normalized, void* onesided, void* signal_sizes) { void* ret = _lantern_Tensor_irfft_tensor_intt_bool_bool_intarrayref(self, signal_ndim, normalized, onesided, signal_sizes); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__fft_with_size_tensor_intt_bool_bool_bool_intarrayref_bool_bool_intarrayref)(void* self, void* signal_ndim, void* complex_input, void* complex_output, void* inverse, void* checked_signal_sizes, void* normalized, void* onesided, void* output_sizes);
  HOST_API void* lantern__fft_with_size_tensor_intt_bool_bool_bool_intarrayref_bool_bool_intarrayref(void* self, void* signal_ndim, void* complex_input, void* complex_output, void* inverse, void* checked_signal_sizes, void* normalized, void* onesided, void* output_sizes) { void* ret = _lantern__fft_with_size_tensor_intt_bool_bool_bool_intarrayref_bool_bool_intarrayref(self, signal_ndim, complex_input, complex_output, inverse, checked_signal_sizes, normalized, onesided, output_sizes); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cufft_get_plan_cache_size_intt)(void* device_index);
  HOST_API void* lantern__cufft_get_plan_cache_size_intt(void* device_index) { void* ret = _lantern__cufft_get_plan_cache_size_intt(device_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cufft_get_plan_cache_max_size_intt)(void* device_index);
  HOST_API void* lantern__cufft_get_plan_cache_max_size_intt(void* device_index) { void* ret = _lantern__cufft_get_plan_cache_max_size_intt(device_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cufft_set_plan_cache_max_size_intt_intt)(void* device_index, void* max_size);
  HOST_API void* lantern__cufft_set_plan_cache_max_size_intt_intt(void* device_index, void* max_size) { void* ret = _lantern__cufft_set_plan_cache_max_size_intt_intt(device_index, max_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cufft_clear_plan_cache_intt)(void* device_index);
  HOST_API void* lantern__cufft_clear_plan_cache_intt(void* device_index) { void* ret = _lantern__cufft_clear_plan_cache_intt(device_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_tensor_tensorlist)(void* self, void* indices);
  HOST_API void* lantern_index_tensor_tensorlist(void* self, void* indices) { void* ret = _lantern_index_tensor_tensorlist(self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_tensor_tensorlist)(void* self, void* indices);
  HOST_API void* lantern_Tensor_index_tensor_tensorlist(void* self, void* indices) { void* ret = _lantern_Tensor_index_tensor_tensorlist(self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_copy__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_copy__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_copy__tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_copy_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_index_copy_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_index_copy_tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_copy_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_copy_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_copy_tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_copy__tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_copy__tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_copy__tensor_dimname_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_copy_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_index_copy_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_index_copy_tensor_dimname_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_copy_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_copy_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_copy_tensor_dimname_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_put__tensor_tensorlist_tensor_bool)(void* self, void* indices, void* values, void* accumulate);
  HOST_API void* lantern_index_put__tensor_tensorlist_tensor_bool(void* self, void* indices, void* values, void* accumulate) { void* ret = _lantern_index_put__tensor_tensorlist_tensor_bool(self, indices, values, accumulate); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_put__tensor_tensorlist_tensor_bool)(void* self, void* indices, void* values, void* accumulate);
  HOST_API void* lantern_Tensor_index_put__tensor_tensorlist_tensor_bool(void* self, void* indices, void* values, void* accumulate) { void* ret = _lantern_Tensor_index_put__tensor_tensorlist_tensor_bool(self, indices, values, accumulate); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_put_tensor_tensorlist_tensor_bool)(void* self, void* indices, void* values, void* accumulate);
  HOST_API void* lantern_index_put_tensor_tensorlist_tensor_bool(void* self, void* indices, void* values, void* accumulate) { void* ret = _lantern_index_put_tensor_tensorlist_tensor_bool(self, indices, values, accumulate); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_put_tensor_tensorlist_tensor_bool)(void* self, void* indices, void* values, void* accumulate);
  HOST_API void* lantern_Tensor_index_put_tensor_tensorlist_tensor_bool(void* self, void* indices, void* values, void* accumulate) { void* ret = _lantern_Tensor_index_put_tensor_tensorlist_tensor_bool(self, indices, values, accumulate); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__index_put_impl__tensor_tensorlist_tensor_bool_bool)(void* self, void* indices, void* values, void* accumulate, void* unsafe);
  HOST_API void* lantern__index_put_impl__tensor_tensorlist_tensor_bool_bool(void* self, void* indices, void* values, void* accumulate, void* unsafe) { void* ret = _lantern__index_put_impl__tensor_tensorlist_tensor_bool_bool(self, indices, values, accumulate, unsafe); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_instance_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* use_input_stats, void* momentum, void* eps, void* cudnn_enabled);
  HOST_API void* lantern_instance_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* use_input_stats, void* momentum, void* eps, void* cudnn_enabled) { void* ret = _lantern_instance_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool(input, weight, bias, running_mean, running_var, use_input_stats, momentum, eps, cudnn_enabled); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_inverse_tensor)(void* self);
  HOST_API void* lantern_inverse_tensor(void* self) { void* ret = _lantern_inverse_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_inverse_tensor)(void* self);
  HOST_API void* lantern_Tensor_inverse_tensor(void* self) { void* ret = _lantern_Tensor_inverse_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_inverse_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_inverse_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_inverse_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__inverse_helper_tensor)(void* self);
  HOST_API void* lantern__inverse_helper_tensor(void* self) { void* ret = _lantern__inverse_helper_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_isclose_tensor_tensor_double_double_bool)(void* self, void* other, void* rtol, void* atol, void* equal_nan);
  HOST_API void* lantern_isclose_tensor_tensor_double_double_bool(void* self, void* other, void* rtol, void* atol, void* equal_nan) { void* ret = _lantern_isclose_tensor_tensor_double_double_bool(self, other, rtol, atol, equal_nan); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_isclose_tensor_tensor_double_double_bool)(void* self, void* other, void* rtol, void* atol, void* equal_nan);
  HOST_API void* lantern_Tensor_isclose_tensor_tensor_double_double_bool(void* self, void* other, void* rtol, void* atol, void* equal_nan) { void* ret = _lantern_Tensor_isclose_tensor_tensor_double_double_bool(self, other, rtol, atol, equal_nan); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_isnan_tensor)(void* self);
  HOST_API void* lantern_isnan_tensor(void* self) { void* ret = _lantern_isnan_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_distributed_tensor)(void* self);
  HOST_API void* lantern_is_distributed_tensor(void* self) { void* ret = _lantern_is_distributed_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_distributed_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_distributed_tensor(void* self) { void* ret = _lantern_Tensor_is_distributed_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_floating_point_tensor)(void* self);
  HOST_API void* lantern_is_floating_point_tensor(void* self) { void* ret = _lantern_is_floating_point_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_floating_point_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_floating_point_tensor(void* self) { void* ret = _lantern_Tensor_is_floating_point_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_complex_tensor)(void* self);
  HOST_API void* lantern_is_complex_tensor(void* self) { void* ret = _lantern_is_complex_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_complex_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_complex_tensor(void* self) { void* ret = _lantern_Tensor_is_complex_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_nonzero_tensor)(void* self);
  HOST_API void* lantern_is_nonzero_tensor(void* self) { void* ret = _lantern_is_nonzero_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_nonzero_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_nonzero_tensor(void* self) { void* ret = _lantern_Tensor_is_nonzero_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_same_size_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_is_same_size_tensor_tensor(void* self, void* other) { void* ret = _lantern_is_same_size_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_same_size_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_is_same_size_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_is_same_size_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_is_signed_tensor)(void* self);
  HOST_API void* lantern_is_signed_tensor(void* self) { void* ret = _lantern_is_signed_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_signed_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_signed_tensor(void* self) { void* ret = _lantern_Tensor_is_signed_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kl_div_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_kl_div_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_kl_div_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kl_div_backward_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_kl_div_backward_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_kl_div_backward_tensor_tensor_tensor_intt(grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kthvalue_tensor_intt_intt_bool)(void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_kthvalue_tensor_intt_intt_bool(void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_kthvalue_tensor_intt_intt_bool(self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_kthvalue_tensor_intt_intt_bool)(void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_kthvalue_tensor_intt_intt_bool(void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_Tensor_kthvalue_tensor_intt_intt_bool(self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kthvalue_out_tensor_tensor_tensor_intt_intt_bool)(void* values, void* indices, void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_kthvalue_out_tensor_tensor_tensor_intt_intt_bool(void* values, void* indices, void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_kthvalue_out_tensor_tensor_tensor_intt_intt_bool(values, indices, self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kthvalue_tensor_intt_dimname_bool)(void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_kthvalue_tensor_intt_dimname_bool(void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_kthvalue_tensor_intt_dimname_bool(self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_kthvalue_tensor_intt_dimname_bool)(void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_kthvalue_tensor_intt_dimname_bool(void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_Tensor_kthvalue_tensor_intt_dimname_bool(self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_kthvalue_out_tensor_tensor_tensor_intt_dimname_bool)(void* values, void* indices, void* self, void* k, void* dim, void* keepdim);
  HOST_API void* lantern_kthvalue_out_tensor_tensor_tensor_intt_dimname_bool(void* values, void* indices, void* self, void* k, void* dim, void* keepdim) { void* ret = _lantern_kthvalue_out_tensor_tensor_tensor_intt_dimname_bool(values, indices, self, k, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_layer_norm_tensor_intarrayref_tensor_tensor_double_bool)(void* input, void* normalized_shape, void* weight, void* bias, void* eps, void* cudnn_enable);
  HOST_API void* lantern_layer_norm_tensor_intarrayref_tensor_tensor_double_bool(void* input, void* normalized_shape, void* weight, void* bias, void* eps, void* cudnn_enable) { void* ret = _lantern_layer_norm_tensor_intarrayref_tensor_tensor_double_bool(input, normalized_shape, weight, bias, eps, cudnn_enable); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_layer_norm_tensor_tensor_tensor_intt_intt_double)(void* input, void* weight, void* bias, void* M, void* N, void* eps);
  HOST_API void* lantern_native_layer_norm_tensor_tensor_tensor_intt_intt_double(void* input, void* weight, void* bias, void* M, void* N, void* eps) { void* ret = _lantern_native_layer_norm_tensor_tensor_tensor_intt_intt_double(input, weight, bias, M, N, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_layer_norm_backward_tensor_tensor_tensor_tensor_tensor_intt_intt_stdarraybool)(void* grad_out, void* input, void* mean, void* rstd, void* weight, void* M, void* N, void* output_mask);
  HOST_API void* lantern_native_layer_norm_backward_tensor_tensor_tensor_tensor_tensor_intt_intt_stdarraybool(void* grad_out, void* input, void* mean, void* rstd, void* weight, void* M, void* N, void* output_mask) { void* ret = _lantern_native_layer_norm_backward_tensor_tensor_tensor_tensor_tensor_intt_intt_stdarraybool(grad_out, input, mean, rstd, weight, M, N, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_linear_tensor_tensor_tensor)(void* input, void* weight, void* bias);
  HOST_API void* lantern_linear_tensor_tensor_tensor(void* input, void* weight, void* bias) { void* ret = _lantern_linear_tensor_tensor_tensor(input, weight, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_linear_tensor_tensor_tensor)(void* input, void* weight, void* bias);
  HOST_API void* lantern_mkldnn_linear_tensor_tensor_tensor(void* input, void* weight, void* bias) { void* ret = _lantern_mkldnn_linear_tensor_tensor_tensor(input, weight, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_linear_int8_weight_fp32_activation_tensor_tensor_tensor_tensor_scalar_scalar_tensor)(void* input, void* weight, void* packed, void* col_offsets, void* weight_scale, void* weight_zero_point, void* bias);
  HOST_API void* lantern_fbgemm_linear_int8_weight_fp32_activation_tensor_tensor_tensor_tensor_scalar_scalar_tensor(void* input, void* weight, void* packed, void* col_offsets, void* weight_scale, void* weight_zero_point, void* bias) { void* ret = _lantern_fbgemm_linear_int8_weight_fp32_activation_tensor_tensor_tensor_tensor_scalar_scalar_tensor(input, weight, packed, col_offsets, weight_scale, weight_zero_point, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_linear_int8_weight_tensor_tensor_tensor_tensor_scalar_scalar_tensor)(void* input, void* weight, void* packed, void* col_offsets, void* weight_scale, void* weight_zero_point, void* bias);
  HOST_API void* lantern_fbgemm_linear_int8_weight_tensor_tensor_tensor_tensor_scalar_scalar_tensor(void* input, void* weight, void* packed, void* col_offsets, void* weight_scale, void* weight_zero_point, void* bias) { void* ret = _lantern_fbgemm_linear_int8_weight_tensor_tensor_tensor_tensor_scalar_scalar_tensor(input, weight, packed, col_offsets, weight_scale, weight_zero_point, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_linear_quantize_weight_tensor)(void* input);
  HOST_API void* lantern_fbgemm_linear_quantize_weight_tensor(void* input) { void* ret = _lantern_fbgemm_linear_quantize_weight_tensor(input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_pack_gemm_matrix_fp16_tensor)(void* input);
  HOST_API void* lantern_fbgemm_pack_gemm_matrix_fp16_tensor(void* input) { void* ret = _lantern_fbgemm_pack_gemm_matrix_fp16_tensor(input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_linear_fp16_weight_fp32_activation_tensor_tensor_tensor)(void* input, void* packed_weight, void* bias);
  HOST_API void* lantern_fbgemm_linear_fp16_weight_fp32_activation_tensor_tensor_tensor(void* input, void* packed_weight, void* bias) { void* ret = _lantern_fbgemm_linear_fp16_weight_fp32_activation_tensor_tensor_tensor(input, packed_weight, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_linear_fp16_weight_tensor_tensor_tensor)(void* input, void* packed_weight, void* bias);
  HOST_API void* lantern_fbgemm_linear_fp16_weight_tensor_tensor_tensor(void* input, void* packed_weight, void* bias) { void* ret = _lantern_fbgemm_linear_fp16_weight_tensor_tensor_tensor(input, packed_weight, bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_pack_quantized_matrix_tensor)(void* input);
  HOST_API void* lantern_fbgemm_pack_quantized_matrix_tensor(void* input) { void* ret = _lantern_fbgemm_pack_quantized_matrix_tensor(input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fbgemm_pack_quantized_matrix_tensor_intt_intt)(void* input, void* K, void* N);
  HOST_API void* lantern_fbgemm_pack_quantized_matrix_tensor_intt_intt(void* input, void* K, void* N) { void* ret = _lantern_fbgemm_pack_quantized_matrix_tensor_intt_intt(input, K, N); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_linspace_scalar_scalar_intt_tensoroptions)(void* start, void* end, void* steps, void* options);
  HOST_API void* lantern_linspace_scalar_scalar_intt_tensoroptions(void* start, void* end, void* steps, void* options) { void* ret = _lantern_linspace_scalar_scalar_intt_tensoroptions(start, end, steps, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_linspace_out_tensor_scalar_scalar_intt)(void* out, void* start, void* end, void* steps);
  HOST_API void* lantern_linspace_out_tensor_scalar_scalar_intt(void* out, void* start, void* end, void* steps) { void* ret = _lantern_linspace_out_tensor_scalar_scalar_intt(out, start, end, steps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_tensor)(void* self);
  HOST_API void* lantern_log_tensor(void* self) { void* ret = _lantern_log_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log_tensor)(void* self);
  HOST_API void* lantern_Tensor_log_tensor(void* self) { void* ret = _lantern_Tensor_log_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log__tensor)(void* self);
  HOST_API void* lantern_log__tensor(void* self) { void* ret = _lantern_log__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log__tensor)(void* self);
  HOST_API void* lantern_Tensor_log__tensor(void* self) { void* ret = _lantern_Tensor_log__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_log_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_log_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log10_tensor)(void* self);
  HOST_API void* lantern_log10_tensor(void* self) { void* ret = _lantern_log10_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log10_tensor)(void* self);
  HOST_API void* lantern_Tensor_log10_tensor(void* self) { void* ret = _lantern_Tensor_log10_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log10__tensor)(void* self);
  HOST_API void* lantern_log10__tensor(void* self) { void* ret = _lantern_log10__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log10__tensor)(void* self);
  HOST_API void* lantern_Tensor_log10__tensor(void* self) { void* ret = _lantern_Tensor_log10__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log10_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_log10_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_log10_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log1p_tensor)(void* self);
  HOST_API void* lantern_log1p_tensor(void* self) { void* ret = _lantern_log1p_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log1p_tensor)(void* self);
  HOST_API void* lantern_Tensor_log1p_tensor(void* self) { void* ret = _lantern_Tensor_log1p_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log1p__tensor)(void* self);
  HOST_API void* lantern_log1p__tensor(void* self) { void* ret = _lantern_log1p__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log1p__tensor)(void* self);
  HOST_API void* lantern_Tensor_log1p__tensor(void* self) { void* ret = _lantern_Tensor_log1p__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log1p_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_log1p_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_log1p_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log2_tensor)(void* self);
  HOST_API void* lantern_log2_tensor(void* self) { void* ret = _lantern_log2_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log2_tensor)(void* self);
  HOST_API void* lantern_Tensor_log2_tensor(void* self) { void* ret = _lantern_Tensor_log2_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log2__tensor)(void* self);
  HOST_API void* lantern_log2__tensor(void* self) { void* ret = _lantern_log2__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log2__tensor)(void* self);
  HOST_API void* lantern_Tensor_log2__tensor(void* self) { void* ret = _lantern_Tensor_log2__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log2_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_log2_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_log2_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logdet_tensor)(void* self);
  HOST_API void* lantern_logdet_tensor(void* self) { void* ret = _lantern_logdet_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logdet_tensor)(void* self);
  HOST_API void* lantern_Tensor_logdet_tensor(void* self) { void* ret = _lantern_Tensor_logdet_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logspace_scalar_scalar_intt_double_tensoroptions)(void* start, void* end, void* steps, void* base, void* options);
  HOST_API void* lantern_logspace_scalar_scalar_intt_double_tensoroptions(void* start, void* end, void* steps, void* base, void* options) { void* ret = _lantern_logspace_scalar_scalar_intt_double_tensoroptions(start, end, steps, base, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logspace_out_tensor_scalar_scalar_intt_double)(void* out, void* start, void* end, void* steps, void* base);
  HOST_API void* lantern_logspace_out_tensor_scalar_scalar_intt_double(void* out, void* start, void* end, void* steps, void* base) { void* ret = _lantern_logspace_out_tensor_scalar_scalar_intt_double(out, start, end, steps, base); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_softmax_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_log_softmax_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_log_softmax_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log_softmax_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_log_softmax_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_log_softmax_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_softmax_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_log_softmax_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_log_softmax_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log_softmax_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_log_softmax_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_log_softmax_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__log_softmax_tensor_intt_bool)(void* self, void* dim, void* half_to_float);
  HOST_API void* lantern__log_softmax_tensor_intt_bool(void* self, void* dim, void* half_to_float) { void* ret = _lantern__log_softmax_tensor_intt_bool(self, dim, half_to_float); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__log_softmax_backward_data_tensor_tensor_intt_tensor)(void* grad_output, void* output, void* dim, void* self);
  HOST_API void* lantern__log_softmax_backward_data_tensor_tensor_intt_tensor(void* grad_output, void* output, void* dim, void* self) { void* ret = _lantern__log_softmax_backward_data_tensor_tensor_intt_tensor(grad_output, output, dim, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logsumexp_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_logsumexp_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_logsumexp_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logsumexp_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_logsumexp_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_logsumexp_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logsumexp_out_tensor_tensor_intarrayref_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_logsumexp_out_tensor_tensor_intarrayref_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_logsumexp_out_tensor_tensor_intarrayref_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logsumexp_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_logsumexp_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_logsumexp_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_logsumexp_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_logsumexp_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_logsumexp_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_logsumexp_out_tensor_tensor_dimnamelist_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_logsumexp_out_tensor_tensor_dimnamelist_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_logsumexp_out_tensor_tensor_dimnamelist_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_margin_ranking_loss_tensor_tensor_tensor_double_intt)(void* input1, void* input2, void* target, void* margin, void* reduction);
  HOST_API void* lantern_margin_ranking_loss_tensor_tensor_tensor_double_intt(void* input1, void* input2, void* target, void* margin, void* reduction) { void* ret = _lantern_margin_ranking_loss_tensor_tensor_tensor_double_intt(input1, input2, target, margin, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_matmul_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_matmul_tensor_tensor(void* self, void* other) { void* ret = _lantern_matmul_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_matmul_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_matmul_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_matmul_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_matmul_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_matmul_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_matmul_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_matrix_rank_tensor_double_bool)(void* self, void* tol, void* symmetric);
  HOST_API void* lantern_matrix_rank_tensor_double_bool(void* self, void* tol, void* symmetric) { void* ret = _lantern_matrix_rank_tensor_double_bool(self, tol, symmetric); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_matrix_rank_tensor_bool)(void* self, void* symmetric);
  HOST_API void* lantern_matrix_rank_tensor_bool(void* self, void* symmetric) { void* ret = _lantern_matrix_rank_tensor_bool(self, symmetric); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_matrix_power_tensor_intt)(void* self, void* n);
  HOST_API void* lantern_matrix_power_tensor_intt(void* self, void* n) { void* ret = _lantern_matrix_power_tensor_intt(self, n); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_matrix_power_tensor_intt)(void* self, void* n);
  HOST_API void* lantern_Tensor_matrix_power_tensor_intt(void* self, void* n) { void* ret = _lantern_Tensor_matrix_power_tensor_intt(self, n); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_max_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_max_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_max_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_out_tensor_tensor_tensor_intt_bool)(void* max, void* max_values, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_out_tensor_tensor_tensor_intt_bool(void* max, void* max_values, void* self, void* dim, void* keepdim) { void* ret = _lantern_max_out_tensor_tensor_tensor_intt_bool(max, max_values, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_values_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_values_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_max_values_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_values_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_max_values_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_max_values_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_max_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_max_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_max_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_out_tensor_tensor_tensor_dimname_bool)(void* max, void* max_values, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_out_tensor_tensor_tensor_dimname_bool(void* max, void* max_values, void* self, void* dim, void* keepdim) { void* ret = _lantern_max_out_tensor_tensor_tensor_dimname_bool(max, max_values, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_values_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_max_values_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_max_values_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_values_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_max_values_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_max_values_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool1d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool1d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool1d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool1d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool1d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool1d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_mkldnn_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_mkldnn_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_quantized_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_quantized_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool3d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool3d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool3d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mean_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_mean_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_mean_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mean_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_Tensor_mean_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_Tensor_mean_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mean_tensor_intarrayref_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_mean_tensor_intarrayref_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_mean_tensor_intarrayref_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mean_tensor_intarrayref_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_mean_tensor_intarrayref_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_mean_tensor_intarrayref_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mean_out_tensor_tensor_intarrayref_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_mean_out_tensor_tensor_intarrayref_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_mean_out_tensor_tensor_intarrayref_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mean_tensor_dimnamelist_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_mean_tensor_dimnamelist_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_mean_tensor_dimnamelist_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mean_tensor_dimnamelist_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_mean_tensor_dimnamelist_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_mean_tensor_dimnamelist_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mean_out_tensor_tensor_dimnamelist_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_mean_out_tensor_tensor_dimnamelist_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_mean_out_tensor_tensor_dimnamelist_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_median_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_median_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_median_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_median_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_median_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_median_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_median_out_tensor_tensor_tensor_intt_bool)(void* values, void* indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_median_out_tensor_tensor_tensor_intt_bool(void* values, void* indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_median_out_tensor_tensor_tensor_intt_bool(values, indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_median_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_median_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_median_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_median_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_median_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_median_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_median_out_tensor_tensor_tensor_dimname_bool)(void* values, void* indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_median_out_tensor_tensor_tensor_dimname_bool(void* values, void* indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_median_out_tensor_tensor_tensor_dimname_bool(values, indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_min_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_min_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_min_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_out_tensor_tensor_tensor_intt_bool)(void* min, void* min_indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_out_tensor_tensor_tensor_intt_bool(void* min, void* min_indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_min_out_tensor_tensor_tensor_intt_bool(min, min_indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_values_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_values_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_min_values_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_values_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_min_values_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_min_values_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_min_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_min_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_min_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_out_tensor_tensor_tensor_dimname_bool)(void* min, void* min_indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_out_tensor_tensor_tensor_dimname_bool(void* min, void* min_indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_min_out_tensor_tensor_tensor_dimname_bool(min, min_indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_values_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_min_values_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_min_values_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_values_tensor_dimnamelist_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_min_values_tensor_dimnamelist_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_min_values_tensor_dimnamelist_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups);
  HOST_API void* lantern_mkldnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups) { void* ret = _lantern_mkldnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt(self, weight, bias, padding, stride, dilation, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool)(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* bias_defined);
  HOST_API void* lantern_mkldnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* bias_defined) { void* ret = _lantern_mkldnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool(self_size, grad_output, weight, padding, stride, dilation, groups, bias_defined); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_convolution_backward_weights_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* bias_defined);
  HOST_API void* lantern_mkldnn_convolution_backward_weights_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* bias_defined) { void* ret = _lantern_mkldnn_convolution_backward_weights_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool(weight_size, grad_output, self, padding, stride, dilation, groups, bias_defined); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* output_mask);
  HOST_API void* lantern_mkldnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* output_mask) { void* ret = _lantern_mkldnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_stdarraybool(self, grad_output, weight, padding, stride, dilation, groups, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* exponential_average_factor, void* epsilon);
  HOST_API void* lantern_miopen_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* exponential_average_factor, void* epsilon) { void* ret = _lantern_miopen_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(input, weight, bias, running_mean, running_var, training, exponential_average_factor, epsilon); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double)(void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var, void* epsilon);
  HOST_API void* lantern_miopen_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double(void* input, void* grad_output, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_var, void* epsilon) { void* ret = _lantern_miopen_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double(input, grad_output, weight, running_mean, running_var, save_mean, save_var, epsilon); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self_size, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask);
  HOST_API void* lantern_miopen_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask) { void* ret = _lantern_miopen_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(self, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_backward_bias_tensor)(void* grad_output);
  HOST_API void* lantern_miopen_convolution_backward_bias_tensor(void* grad_output) { void* ret = _lantern_miopen_convolution_backward_bias_tensor(grad_output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(weight_size, grad_output, self, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* bias, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* bias, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, bias, padding, output_padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask);
  HOST_API void* lantern_miopen_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* output_padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask) { void* ret = _lantern_miopen_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(self, grad_output, weight, padding, output_padding, stride, dilation, groups, benchmark, deterministic, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(weight_size, grad_output, self, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_depthwise_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_depthwise_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self, void* weight, void* bias, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_depthwise_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self, weight, bias, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_depthwise_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_depthwise_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* self_size, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_depthwise_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(self_size, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_depthwise_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask);
  HOST_API void* lantern_miopen_depthwise_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(void* self, void* grad_output, void* weight, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic, void* output_mask) { void* ret = _lantern_miopen_depthwise_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool(self, grad_output, weight, padding, stride, dilation, groups, benchmark, deterministic, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_depthwise_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic);
  HOST_API void* lantern_miopen_depthwise_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(void* weight_size, void* grad_output, void* self, void* padding, void* stride, void* dilation, void* groups, void* benchmark, void* deterministic) { void* ret = _lantern_miopen_depthwise_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool(weight_size, grad_output, self, padding, stride, dilation, groups, benchmark, deterministic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_rnn_tensor_tensorlist_intt_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor)(void* input, void* weight, void* weight_stride0, void* hx, void* cx, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state);
  HOST_API void* lantern_miopen_rnn_tensor_tensorlist_intt_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor(void* input, void* weight, void* weight_stride0, void* hx, void* cx, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state) { void* ret = _lantern_miopen_rnn_tensor_tensorlist_intt_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor(input, weight, weight_stride0, hx, cx, mode, hidden_size, num_layers, batch_first, dropout, train, bidirectional, batch_sizes, dropout_state); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_miopen_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool)(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* output, void* grad_output, void* grad_hy, void* grad_cy, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state, void* reserve, void* output_mask);
  HOST_API void* lantern_miopen_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool(void* input, void* weight, void* weight_stride0, void* weight_buf, void* hx, void* cx, void* output, void* grad_output, void* grad_hy, void* grad_cy, void* mode, void* hidden_size, void* num_layers, void* batch_first, void* dropout, void* train, void* bidirectional, void* batch_sizes, void* dropout_state, void* reserve, void* output_mask) { void* ret = _lantern_miopen_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool(input, weight, weight_stride0, weight_buf, hx, cx, output, grad_output, grad_hy, grad_cy, mode, hidden_size, num_layers, batch_first, dropout, train, bidirectional, batch_sizes, dropout_state, reserve, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_mm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_mm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_Tensor_mm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_Tensor_mm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mm_out_tensor_tensor_tensor)(void* out, void* self, void* mat2);
  HOST_API void* lantern_mm_out_tensor_tensor_tensor(void* out, void* self, void* mat2) { void* ret = _lantern_mm_out_tensor_tensor_tensor(out, self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_mm_tensor_tensor)(void* sparse, void* dense);
  HOST_API void* lantern__sparse_mm_tensor_tensor(void* sparse, void* dense) { void* ret = _lantern__sparse_mm_tensor_tensor(sparse, dense); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mode_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_mode_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_mode_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mode_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_mode_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_mode_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mode_out_tensor_tensor_tensor_intt_bool)(void* values, void* indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_mode_out_tensor_tensor_tensor_intt_bool(void* values, void* indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_mode_out_tensor_tensor_tensor_intt_bool(values, indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mode_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_mode_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_mode_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mode_tensor_dimname_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_mode_tensor_dimname_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_Tensor_mode_tensor_dimname_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mode_out_tensor_tensor_tensor_dimname_bool)(void* values, void* indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_mode_out_tensor_tensor_tensor_dimname_bool(void* values, void* indices, void* self, void* dim, void* keepdim) { void* ret = _lantern_mode_out_tensor_tensor_tensor_dimname_bool(values, indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mul_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_mul_tensor_tensor(void* self, void* other) { void* ret = _lantern_mul_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mul_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_mul_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_mul_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mul__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_mul__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_mul__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mul_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_mul_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_mul_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mul_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_mul_tensor_scalar(void* self, void* other) { void* ret = _lantern_mul_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mul_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_mul_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_mul_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mul__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_mul__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_mul__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mv_tensor_tensor)(void* self, void* vec);
  HOST_API void* lantern_mv_tensor_tensor(void* self, void* vec) { void* ret = _lantern_mv_tensor_tensor(self, vec); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mv_tensor_tensor)(void* self, void* vec);
  HOST_API void* lantern_Tensor_mv_tensor_tensor(void* self, void* vec) { void* ret = _lantern_Tensor_mv_tensor_tensor(self, vec); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mv_out_tensor_tensor_tensor)(void* out, void* self, void* vec);
  HOST_API void* lantern_mv_out_tensor_tensor_tensor(void* out, void* self, void* vec) { void* ret = _lantern_mv_out_tensor_tensor_tensor(out, self, vec); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mvlgamma_tensor_intt)(void* self, void* p);
  HOST_API void* lantern_mvlgamma_tensor_intt(void* self, void* p) { void* ret = _lantern_mvlgamma_tensor_intt(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mvlgamma_tensor_intt)(void* self, void* p);
  HOST_API void* lantern_Tensor_mvlgamma_tensor_intt(void* self, void* p) { void* ret = _lantern_Tensor_mvlgamma_tensor_intt(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_mvlgamma__tensor_intt)(void* self, void* p);
  HOST_API void* lantern_Tensor_mvlgamma__tensor_intt(void* self, void* p) { void* ret = _lantern_Tensor_mvlgamma__tensor_intt(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_narrow_copy_tensor_intt_intt_intt)(void* self, void* dim, void* start, void* length);
  HOST_API void* lantern_Tensor_narrow_copy_tensor_intt_intt_intt(void* self, void* dim, void* start, void* length) { void* ret = _lantern_Tensor_narrow_copy_tensor_intt_intt_intt(self, dim, start, length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_narrow_tensor_intt_intt_intt)(void* self, void* dim, void* start, void* length);
  HOST_API void* lantern_narrow_tensor_intt_intt_intt(void* self, void* dim, void* start, void* length) { void* ret = _lantern_narrow_tensor_intt_intt_intt(self, dim, start, length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_narrow_tensor_intt_intt_intt)(void* self, void* dim, void* start, void* length);
  HOST_API void* lantern_Tensor_narrow_tensor_intt_intt_intt(void* self, void* dim, void* start, void* length) { void* ret = _lantern_Tensor_narrow_tensor_intt_intt_intt(self, dim, start, length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_narrow_tensor_intt_tensor_intt)(void* self, void* dim, void* start, void* length);
  HOST_API void* lantern_narrow_tensor_intt_tensor_intt(void* self, void* dim, void* start, void* length) { void* ret = _lantern_narrow_tensor_intt_tensor_intt(self, dim, start, length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_narrow_tensor_intt_tensor_intt)(void* self, void* dim, void* start, void* length);
  HOST_API void* lantern_Tensor_narrow_tensor_intt_tensor_intt(void* self, void* dim, void* start, void* length) { void* ret = _lantern_Tensor_narrow_tensor_intt_tensor_intt(self, dim, start, length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps);
  HOST_API void* lantern_native_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps) { void* ret = _lantern_native_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double(input, weight, bias, running_mean, running_var, training, momentum, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_batch_norm_out_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_double)(void* out, void* save_mean, void* save_invstd, void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps);
  HOST_API void* lantern_native_batch_norm_out_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_double(void* out, void* save_mean, void* save_invstd, void* input, void* weight, void* bias, void* running_mean, void* running_var, void* training, void* momentum, void* eps) { void* ret = _lantern_native_batch_norm_out_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_double(out, save_mean, save_invstd, input, weight, bias, running_mean, running_var, training, momentum, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_stats_tensor_double)(void* input, void* eps);
  HOST_API void* lantern_batch_norm_stats_tensor_double(void* input, void* eps) { void* ret = _lantern_batch_norm_stats_tensor_double(input, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_elemt_tensor_tensor_tensor_tensor_tensor_double)(void* input, void* weight, void* bias, void* mean, void* invstd, void* eps);
  HOST_API void* lantern_batch_norm_elemt_tensor_tensor_tensor_tensor_tensor_double(void* input, void* weight, void* bias, void* mean, void* invstd, void* eps) { void* ret = _lantern_batch_norm_elemt_tensor_tensor_tensor_tensor_tensor_double(input, weight, bias, mean, invstd, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_elemt_out_tensor_tensor_tensor_tensor_tensor_tensor_double)(void* out, void* input, void* weight, void* bias, void* mean, void* invstd, void* eps);
  HOST_API void* lantern_batch_norm_elemt_out_tensor_tensor_tensor_tensor_tensor_tensor_double(void* out, void* input, void* weight, void* bias, void* mean, void* invstd, void* eps) { void* ret = _lantern_batch_norm_elemt_out_tensor_tensor_tensor_tensor_tensor_tensor_double(out, input, weight, bias, mean, invstd, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_gather_stats_tensor_tensor_tensor_tensor_tensor_double_double_intt)(void* input, void* mean, void* invstd, void* running_mean, void* running_var, void* momentum, void* eps, void* count);
  HOST_API void* lantern_batch_norm_gather_stats_tensor_tensor_tensor_tensor_tensor_double_double_intt(void* input, void* mean, void* invstd, void* running_mean, void* running_var, void* momentum, void* eps, void* count) { void* ret = _lantern_batch_norm_gather_stats_tensor_tensor_tensor_tensor_tensor_double_double_intt(input, mean, invstd, running_mean, running_var, momentum, eps, count); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_gather_stats_with_counts_tensor_tensor_tensor_tensor_tensor_double_double_intarrayref)(void* input, void* mean, void* invstd, void* running_mean, void* running_var, void* momentum, void* eps, void* counts);
  HOST_API void* lantern_batch_norm_gather_stats_with_counts_tensor_tensor_tensor_tensor_tensor_double_double_intarrayref(void* input, void* mean, void* invstd, void* running_mean, void* running_var, void* momentum, void* eps, void* counts) { void* ret = _lantern_batch_norm_gather_stats_with_counts_tensor_tensor_tensor_tensor_tensor_double_double_intarrayref(input, mean, invstd, running_mean, running_var, momentum, eps, counts); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool)(void* grad_out, void* input, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_invstd, void* train, void* eps, void* output_mask);
  HOST_API void* lantern_native_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool(void* grad_out, void* input, void* weight, void* running_mean, void* running_var, void* save_mean, void* save_invstd, void* train, void* eps, void* output_mask) { void* ret = _lantern_native_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool(grad_out, input, weight, running_mean, running_var, save_mean, save_invstd, train, eps, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_backward_reduce_tensor_tensor_tensor_tensor_tensor_bool_bool_bool)(void* grad_out, void* input, void* mean, void* invstd, void* weight, void* input_g, void* weight_g, void* bias_g);
  HOST_API void* lantern_batch_norm_backward_reduce_tensor_tensor_tensor_tensor_tensor_bool_bool_bool(void* grad_out, void* input, void* mean, void* invstd, void* weight, void* input_g, void* weight_g, void* bias_g) { void* ret = _lantern_batch_norm_backward_reduce_tensor_tensor_tensor_tensor_tensor_bool_bool_bool(grad_out, input, mean, invstd, weight, input_g, weight_g, bias_g); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_backward_elemt_tensor_tensor_tensor_tensor_tensor_tensor_tensor)(void* grad_out, void* input, void* mean, void* invstd, void* weight, void* mean_dy, void* mean_dy_xmu);
  HOST_API void* lantern_batch_norm_backward_elemt_tensor_tensor_tensor_tensor_tensor_tensor_tensor(void* grad_out, void* input, void* mean, void* invstd, void* weight, void* mean_dy, void* mean_dy_xmu) { void* ret = _lantern_batch_norm_backward_elemt_tensor_tensor_tensor_tensor_tensor_tensor_tensor(grad_out, input, mean, invstd, weight, mean_dy, mean_dy_xmu); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_batch_norm_update_stats_tensor_tensor_tensor_double)(void* input, void* running_mean, void* running_var, void* momentum);
  HOST_API void* lantern_batch_norm_update_stats_tensor_tensor_tensor_double(void* input, void* running_mean, void* running_var, void* momentum) { void* ret = _lantern_batch_norm_update_stats_tensor_tensor_tensor_double(input, running_mean, running_var, momentum); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__nnpack_available)();
  HOST_API void* lantern__nnpack_available() { void* ret = _lantern__nnpack_available(); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__nnpack_spatial_convolution_tensor_tensor_tensor_intarrayref_intarrayref)(void* input, void* weight, void* bias, void* padding, void* stride);
  HOST_API void* lantern__nnpack_spatial_convolution_tensor_tensor_tensor_intarrayref_intarrayref(void* input, void* weight, void* bias, void* padding, void* stride) { void* ret = _lantern__nnpack_spatial_convolution_tensor_tensor_tensor_intarrayref_intarrayref(input, weight, bias, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__nnpack_spatial_convolution_backward_tensor_tensor_tensor_intarrayref_stdarraybool)(void* input, void* grad_output, void* weight, void* padding, void* output_mask);
  HOST_API void* lantern__nnpack_spatial_convolution_backward_tensor_tensor_tensor_intarrayref_stdarraybool(void* input, void* grad_output, void* weight, void* padding, void* output_mask) { void* ret = _lantern__nnpack_spatial_convolution_backward_tensor_tensor_tensor_intarrayref_stdarraybool(input, grad_output, weight, padding, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__nnpack_spatial_convolution_backward_input_tensor_tensor_tensor_intarrayref)(void* input, void* grad_output, void* weight, void* padding);
  HOST_API void* lantern__nnpack_spatial_convolution_backward_input_tensor_tensor_tensor_intarrayref(void* input, void* grad_output, void* weight, void* padding) { void* ret = _lantern__nnpack_spatial_convolution_backward_input_tensor_tensor_tensor_intarrayref(input, grad_output, weight, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__nnpack_spatial_convolution_backward_weight_tensor_intarrayref_tensor_intarrayref)(void* input, void* weightsize, void* grad_output, void* padding);
  HOST_API void* lantern__nnpack_spatial_convolution_backward_weight_tensor_intarrayref_tensor_intarrayref(void* input, void* weightsize, void* grad_output, void* padding) { void* ret = _lantern__nnpack_spatial_convolution_backward_weight_tensor_intarrayref_tensor_intarrayref(input, weightsize, grad_output, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ones_intarrayref_dimnamelist_tensoroptions)(void* size, void* names, void* options);
  HOST_API void* lantern_ones_intarrayref_dimnamelist_tensoroptions(void* size, void* names, void* options) { void* ret = _lantern_ones_intarrayref_dimnamelist_tensoroptions(size, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ones_intarrayref_tensoroptions)(void* size, void* options);
  HOST_API void* lantern_ones_intarrayref_tensoroptions(void* size, void* options) { void* ret = _lantern_ones_intarrayref_tensoroptions(size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ones_out_tensor_intarrayref)(void* out, void* size);
  HOST_API void* lantern_ones_out_tensor_intarrayref(void* out, void* size) { void* ret = _lantern_ones_out_tensor_intarrayref(out, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ones_like_tensor_tensoroptions_memoryformat)(void* self, void* options, void* memory_format);
  HOST_API void* lantern_ones_like_tensor_tensoroptions_memoryformat(void* self, void* options, void* memory_format) { void* ret = _lantern_ones_like_tensor_tensoroptions_memoryformat(self, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pairwise_distance_tensor_tensor_double_double_bool)(void* x1, void* x2, void* p, void* eps, void* keepdim);
  HOST_API void* lantern_pairwise_distance_tensor_tensor_double_double_bool(void* x1, void* x2, void* p, void* eps, void* keepdim) { void* ret = _lantern_pairwise_distance_tensor_tensor_double_double_bool(x1, x2, p, eps, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cdist_tensor_tensor_double_intt)(void* x1, void* x2, void* p, void* compute_mode);
  HOST_API void* lantern_cdist_tensor_tensor_double_intt(void* x1, void* x2, void* p, void* compute_mode) { void* ret = _lantern_cdist_tensor_tensor_double_intt(x1, x2, p, compute_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cdist_forward_tensor_tensor_double_intt)(void* x1, void* x2, void* p, void* compute_mode);
  HOST_API void* lantern__cdist_forward_tensor_tensor_double_intt(void* x1, void* x2, void* p, void* compute_mode) { void* ret = _lantern__cdist_forward_tensor_tensor_double_intt(x1, x2, p, compute_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cdist_backward_tensor_tensor_tensor_double_tensor)(void* grad, void* x1, void* x2, void* p, void* cdist);
  HOST_API void* lantern__cdist_backward_tensor_tensor_tensor_double_tensor(void* grad, void* x1, void* x2, void* p, void* cdist) { void* ret = _lantern__cdist_backward_tensor_tensor_tensor_double_tensor(grad, x1, x2, p, cdist); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pdist_tensor_double)(void* self, void* p);
  HOST_API void* lantern_pdist_tensor_double(void* self, void* p) { void* ret = _lantern_pdist_tensor_double(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__pdist_forward_tensor_double)(void* self, void* p);
  HOST_API void* lantern__pdist_forward_tensor_double(void* self, void* p) { void* ret = _lantern__pdist_forward_tensor_double(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__pdist_backward_tensor_tensor_double_tensor)(void* grad, void* self, void* p, void* pdist);
  HOST_API void* lantern__pdist_backward_tensor_tensor_double_tensor(void* grad, void* self, void* p, void* pdist) { void* ret = _lantern__pdist_backward_tensor_tensor_double_tensor(grad, self, p, pdist); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cosine_similarity_tensor_tensor_intt_double)(void* x1, void* x2, void* dim, void* eps);
  HOST_API void* lantern_cosine_similarity_tensor_tensor_intt_double(void* x1, void* x2, void* dim, void* eps) { void* ret = _lantern_cosine_similarity_tensor_tensor_intt_double(x1, x2, dim, eps); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_permute_tensor_intarrayref)(void* self, void* dims);
  HOST_API void* lantern_Tensor_permute_tensor_intarrayref(void* self, void* dims) { void* ret = _lantern_Tensor_permute_tensor_intarrayref(self, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_numpy_t_tensor)(void* self);
  HOST_API void* lantern_Tensor_numpy_t_tensor(void* self) { void* ret = _lantern_Tensor_numpy_t_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pixel_shuffle_tensor_intt)(void* self, void* upscale_factor);
  HOST_API void* lantern_pixel_shuffle_tensor_intt(void* self, void* upscale_factor) { void* ret = _lantern_pixel_shuffle_tensor_intt(self, upscale_factor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_pinned_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_pinned_tensor(void* self) { void* ret = _lantern_Tensor_is_pinned_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pin_memory_tensor)(void* self);
  HOST_API void* lantern_Tensor_pin_memory_tensor(void* self) { void* ret = _lantern_Tensor_pin_memory_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pinverse_tensor_double)(void* self, void* rcond);
  HOST_API void* lantern_pinverse_tensor_double(void* self, void* rcond) { void* ret = _lantern_pinverse_tensor_double(self, rcond); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pinverse_tensor_double)(void* self, void* rcond);
  HOST_API void* lantern_Tensor_pinverse_tensor_double(void* self, void* rcond) { void* ret = _lantern_Tensor_pinverse_tensor_double(self, rcond); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_poisson_nll_loss_tensor_tensor_bool_bool_double_intt)(void* input, void* target, void* log_input, void* full, void* eps, void* reduction);
  HOST_API void* lantern_poisson_nll_loss_tensor_tensor_bool_bool_double_intt(void* input, void* target, void* log_input, void* full, void* eps, void* reduction) { void* ret = _lantern_poisson_nll_loss_tensor_tensor_bool_bool_double_intt(input, target, log_input, full, eps, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scalar_tensor_scalar_tensoroptions)(void* s, void* options);
  HOST_API void* lantern_scalar_tensor_scalar_tensoroptions(void* s, void* options) { void* ret = _lantern_scalar_tensor_scalar_tensoroptions(s, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_intarrayref_dimnamelist_tensoroptions)(void* size, void* names, void* options);
  HOST_API void* lantern_rand_intarrayref_dimnamelist_tensoroptions(void* size, void* names, void* options) { void* ret = _lantern_rand_intarrayref_dimnamelist_tensoroptions(size, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_intarrayref_generator_dimnamelist_tensoroptions)(void* size, void* generator, void* names, void* options);
  HOST_API void* lantern_rand_intarrayref_generator_dimnamelist_tensoroptions(void* size, void* generator, void* names, void* options) { void* ret = _lantern_rand_intarrayref_generator_dimnamelist_tensoroptions(size, generator, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_intarrayref_tensoroptions)(void* size, void* options);
  HOST_API void* lantern_rand_intarrayref_tensoroptions(void* size, void* options) { void* ret = _lantern_rand_intarrayref_tensoroptions(size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_intarrayref_generator_tensoroptions)(void* size, void* generator, void* options);
  HOST_API void* lantern_rand_intarrayref_generator_tensoroptions(void* size, void* generator, void* options) { void* ret = _lantern_rand_intarrayref_generator_tensoroptions(size, generator, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_out_tensor_intarrayref)(void* out, void* size);
  HOST_API void* lantern_rand_out_tensor_intarrayref(void* out, void* size) { void* ret = _lantern_rand_out_tensor_intarrayref(out, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_out_tensor_intarrayref_generator)(void* out, void* size, void* generator);
  HOST_API void* lantern_rand_out_tensor_intarrayref_generator(void* out, void* size, void* generator) { void* ret = _lantern_rand_out_tensor_intarrayref_generator(out, size, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rand_like_tensor_tensoroptions_memoryformat)(void* self, void* options, void* memory_format);
  HOST_API void* lantern_rand_like_tensor_tensoroptions_memoryformat(void* self, void* options, void* memory_format) { void* ret = _lantern_rand_like_tensor_tensoroptions_memoryformat(self, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_intt_intarrayref_tensoroptions)(void* high, void* size, void* options);
  HOST_API void* lantern_randint_intt_intarrayref_tensoroptions(void* high, void* size, void* options) { void* ret = _lantern_randint_intt_intarrayref_tensoroptions(high, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_intt_intarrayref_generator_tensoroptions)(void* high, void* size, void* generator, void* options);
  HOST_API void* lantern_randint_intt_intarrayref_generator_tensoroptions(void* high, void* size, void* generator, void* options) { void* ret = _lantern_randint_intt_intarrayref_generator_tensoroptions(high, size, generator, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_intt_intt_intarrayref_tensoroptions)(void* low, void* high, void* size, void* options);
  HOST_API void* lantern_randint_intt_intt_intarrayref_tensoroptions(void* low, void* high, void* size, void* options) { void* ret = _lantern_randint_intt_intt_intarrayref_tensoroptions(low, high, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_intt_intt_intarrayref_generator_tensoroptions)(void* low, void* high, void* size, void* generator, void* options);
  HOST_API void* lantern_randint_intt_intt_intarrayref_generator_tensoroptions(void* low, void* high, void* size, void* generator, void* options) { void* ret = _lantern_randint_intt_intt_intarrayref_generator_tensoroptions(low, high, size, generator, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_out_tensor_intt_intarrayref)(void* out, void* high, void* size);
  HOST_API void* lantern_randint_out_tensor_intt_intarrayref(void* out, void* high, void* size) { void* ret = _lantern_randint_out_tensor_intt_intarrayref(out, high, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_out_tensor_intt_intarrayref_generator)(void* out, void* high, void* size, void* generator);
  HOST_API void* lantern_randint_out_tensor_intt_intarrayref_generator(void* out, void* high, void* size, void* generator) { void* ret = _lantern_randint_out_tensor_intt_intarrayref_generator(out, high, size, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_out_tensor_intt_intt_intarrayref)(void* out, void* low, void* high, void* size);
  HOST_API void* lantern_randint_out_tensor_intt_intt_intarrayref(void* out, void* low, void* high, void* size) { void* ret = _lantern_randint_out_tensor_intt_intt_intarrayref(out, low, high, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_out_tensor_intt_intt_intarrayref_generator)(void* out, void* low, void* high, void* size, void* generator);
  HOST_API void* lantern_randint_out_tensor_intt_intt_intarrayref_generator(void* out, void* low, void* high, void* size, void* generator) { void* ret = _lantern_randint_out_tensor_intt_intt_intarrayref_generator(out, low, high, size, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_like_tensor_intt_tensoroptions_memoryformat)(void* self, void* high, void* options, void* memory_format);
  HOST_API void* lantern_randint_like_tensor_intt_tensoroptions_memoryformat(void* self, void* high, void* options, void* memory_format) { void* ret = _lantern_randint_like_tensor_intt_tensoroptions_memoryformat(self, high, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randint_like_tensor_intt_intt_tensoroptions_memoryformat)(void* self, void* low, void* high, void* options, void* memory_format);
  HOST_API void* lantern_randint_like_tensor_intt_intt_tensoroptions_memoryformat(void* self, void* low, void* high, void* options, void* memory_format) { void* ret = _lantern_randint_like_tensor_intt_intt_tensoroptions_memoryformat(self, low, high, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_intarrayref_tensoroptions)(void* size, void* options);
  HOST_API void* lantern_randn_intarrayref_tensoroptions(void* size, void* options) { void* ret = _lantern_randn_intarrayref_tensoroptions(size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_intarrayref_generator_tensoroptions)(void* size, void* generator, void* options);
  HOST_API void* lantern_randn_intarrayref_generator_tensoroptions(void* size, void* generator, void* options) { void* ret = _lantern_randn_intarrayref_generator_tensoroptions(size, generator, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_intarrayref_dimnamelist_tensoroptions)(void* size, void* names, void* options);
  HOST_API void* lantern_randn_intarrayref_dimnamelist_tensoroptions(void* size, void* names, void* options) { void* ret = _lantern_randn_intarrayref_dimnamelist_tensoroptions(size, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_intarrayref_generator_dimnamelist_tensoroptions)(void* size, void* generator, void* names, void* options);
  HOST_API void* lantern_randn_intarrayref_generator_dimnamelist_tensoroptions(void* size, void* generator, void* names, void* options) { void* ret = _lantern_randn_intarrayref_generator_dimnamelist_tensoroptions(size, generator, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_out_tensor_intarrayref)(void* out, void* size);
  HOST_API void* lantern_randn_out_tensor_intarrayref(void* out, void* size) { void* ret = _lantern_randn_out_tensor_intarrayref(out, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_out_tensor_intarrayref_generator)(void* out, void* size, void* generator);
  HOST_API void* lantern_randn_out_tensor_intarrayref_generator(void* out, void* size, void* generator) { void* ret = _lantern_randn_out_tensor_intarrayref_generator(out, size, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randn_like_tensor_tensoroptions_memoryformat)(void* self, void* options, void* memory_format);
  HOST_API void* lantern_randn_like_tensor_tensoroptions_memoryformat(void* self, void* options, void* memory_format) { void* ret = _lantern_randn_like_tensor_tensoroptions_memoryformat(self, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randperm_intt_tensoroptions)(void* n, void* options);
  HOST_API void* lantern_randperm_intt_tensoroptions(void* n, void* options) { void* ret = _lantern_randperm_intt_tensoroptions(n, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randperm_intt_generator_tensoroptions)(void* n, void* generator, void* options);
  HOST_API void* lantern_randperm_intt_generator_tensoroptions(void* n, void* generator, void* options) { void* ret = _lantern_randperm_intt_generator_tensoroptions(n, generator, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randperm_out_tensor_intt)(void* out, void* n);
  HOST_API void* lantern_randperm_out_tensor_intt(void* out, void* n) { void* ret = _lantern_randperm_out_tensor_intt(out, n); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_randperm_out_tensor_intt_generator)(void* out, void* n, void* generator);
  HOST_API void* lantern_randperm_out_tensor_intt_generator(void* out, void* n, void* generator) { void* ret = _lantern_randperm_out_tensor_intt_generator(out, n, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_range_scalar_scalar_scalar_tensoroptions)(void* start, void* end, void* step, void* options);
  HOST_API void* lantern_range_scalar_scalar_scalar_tensoroptions(void* start, void* end, void* step, void* options) { void* ret = _lantern_range_scalar_scalar_scalar_tensoroptions(start, end, step, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_range_scalar_scalar_tensoroptions)(void* start, void* end, void* options);
  HOST_API void* lantern_range_scalar_scalar_tensoroptions(void* start, void* end, void* options) { void* ret = _lantern_range_scalar_scalar_tensoroptions(start, end, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_range_out_tensor_scalar_scalar_scalar)(void* out, void* start, void* end, void* step);
  HOST_API void* lantern_range_out_tensor_scalar_scalar_scalar(void* out, void* start, void* end, void* step) { void* ret = _lantern_range_out_tensor_scalar_scalar_scalar(out, start, end, step); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reciprocal_tensor)(void* self);
  HOST_API void* lantern_reciprocal_tensor(void* self) { void* ret = _lantern_reciprocal_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_reciprocal_tensor)(void* self);
  HOST_API void* lantern_Tensor_reciprocal_tensor(void* self) { void* ret = _lantern_Tensor_reciprocal_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reciprocal__tensor)(void* self);
  HOST_API void* lantern_reciprocal__tensor(void* self) { void* ret = _lantern_reciprocal__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_reciprocal__tensor)(void* self);
  HOST_API void* lantern_Tensor_reciprocal__tensor(void* self) { void* ret = _lantern_Tensor_reciprocal__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reciprocal_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_reciprocal_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_reciprocal_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_neg_tensor)(void* self);
  HOST_API void* lantern_neg_tensor(void* self) { void* ret = _lantern_neg_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_neg_tensor)(void* self);
  HOST_API void* lantern_Tensor_neg_tensor(void* self) { void* ret = _lantern_Tensor_neg_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_neg__tensor)(void* self);
  HOST_API void* lantern_neg__tensor(void* self) { void* ret = _lantern_neg__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_neg__tensor)(void* self);
  HOST_API void* lantern_Tensor_neg__tensor(void* self) { void* ret = _lantern_Tensor_neg__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_neg_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_neg_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_neg_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_repeat_tensor_intarrayref)(void* self, void* repeats);
  HOST_API void* lantern_Tensor_repeat_tensor_intarrayref(void* self, void* repeats) { void* ret = _lantern_Tensor_repeat_tensor_intarrayref(self, repeats); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_repeat_interleave_tensor)(void* repeats);
  HOST_API void* lantern_repeat_interleave_tensor(void* repeats) { void* ret = _lantern_repeat_interleave_tensor(repeats); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_repeat_interleave_tensor_tensor_intt)(void* self, void* repeats, void* dim);
  HOST_API void* lantern_repeat_interleave_tensor_tensor_intt(void* self, void* repeats, void* dim) { void* ret = _lantern_repeat_interleave_tensor_tensor_intt(self, repeats, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_repeat_interleave_tensor_tensor_intt)(void* self, void* repeats, void* dim);
  HOST_API void* lantern_Tensor_repeat_interleave_tensor_tensor_intt(void* self, void* repeats, void* dim) { void* ret = _lantern_Tensor_repeat_interleave_tensor_tensor_intt(self, repeats, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_repeat_interleave_tensor_intt_intt)(void* self, void* repeats, void* dim);
  HOST_API void* lantern_repeat_interleave_tensor_intt_intt(void* self, void* repeats, void* dim) { void* ret = _lantern_repeat_interleave_tensor_intt_intt(self, repeats, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_repeat_interleave_tensor_intt_intt)(void* self, void* repeats, void* dim);
  HOST_API void* lantern_Tensor_repeat_interleave_tensor_intt_intt(void* self, void* repeats, void* dim) { void* ret = _lantern_Tensor_repeat_interleave_tensor_intt_intt(self, repeats, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reshape_tensor_intarrayref)(void* self, void* shape);
  HOST_API void* lantern_reshape_tensor_intarrayref(void* self, void* shape) { void* ret = _lantern_reshape_tensor_intarrayref(self, shape); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_reshape_tensor_intarrayref)(void* self, void* shape);
  HOST_API void* lantern_Tensor_reshape_tensor_intarrayref(void* self, void* shape) { void* ret = _lantern_Tensor_reshape_tensor_intarrayref(self, shape); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__mkldnn_reshape_tensor_intarrayref)(void* self, void* shape);
  HOST_API void* lantern__mkldnn_reshape_tensor_intarrayref(void* self, void* shape) { void* ret = _lantern__mkldnn_reshape_tensor_intarrayref(self, shape); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_reshape_as_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_reshape_as_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_reshape_as_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_round_tensor)(void* self);
  HOST_API void* lantern_round_tensor(void* self) { void* ret = _lantern_round_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_round_tensor)(void* self);
  HOST_API void* lantern_Tensor_round_tensor(void* self) { void* ret = _lantern_Tensor_round_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_round__tensor)(void* self);
  HOST_API void* lantern_round__tensor(void* self) { void* ret = _lantern_round__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_round__tensor)(void* self);
  HOST_API void* lantern_Tensor_round__tensor(void* self) { void* ret = _lantern_Tensor_round__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_round_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_round_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_round_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu_tensor_scalar_scalar_bool_generator)(void* self, void* lower, void* upper, void* training, void* generator);
  HOST_API void* lantern_rrelu_tensor_scalar_scalar_bool_generator(void* self, void* lower, void* upper, void* training, void* generator) { void* ret = _lantern_rrelu_tensor_scalar_scalar_bool_generator(self, lower, upper, training, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu__tensor_scalar_scalar_bool_generator)(void* self, void* lower, void* upper, void* training, void* generator);
  HOST_API void* lantern_rrelu__tensor_scalar_scalar_bool_generator(void* self, void* lower, void* upper, void* training, void* generator) { void* ret = _lantern_rrelu__tensor_scalar_scalar_bool_generator(self, lower, upper, training, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_relu_tensor)(void* self);
  HOST_API void* lantern_relu_tensor(void* self) { void* ret = _lantern_relu_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_relu_tensor)(void* self);
  HOST_API void* lantern_Tensor_relu_tensor(void* self) { void* ret = _lantern_Tensor_relu_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_relu__tensor)(void* self);
  HOST_API void* lantern_relu__tensor(void* self) { void* ret = _lantern_relu__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_relu__tensor)(void* self);
  HOST_API void* lantern_Tensor_relu__tensor(void* self) { void* ret = _lantern_Tensor_relu__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prelu_tensor_tensor)(void* self, void* weight);
  HOST_API void* lantern_prelu_tensor_tensor(void* self, void* weight) { void* ret = _lantern_prelu_tensor_tensor(self, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_prelu_tensor_tensor)(void* self, void* weight);
  HOST_API void* lantern_Tensor_prelu_tensor_tensor(void* self, void* weight) { void* ret = _lantern_Tensor_prelu_tensor_tensor(self, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prelu_backward_tensor_tensor_tensor)(void* grad_output, void* self, void* weight);
  HOST_API void* lantern_prelu_backward_tensor_tensor_tensor(void* grad_output, void* self, void* weight) { void* ret = _lantern_prelu_backward_tensor_tensor_tensor(grad_output, self, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_prelu_backward_tensor_tensor_tensor)(void* grad_output, void* self, void* weight);
  HOST_API void* lantern_Tensor_prelu_backward_tensor_tensor_tensor(void* grad_output, void* self, void* weight) { void* ret = _lantern_Tensor_prelu_backward_tensor_tensor_tensor(grad_output, self, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gelu_tensor)(void* self);
  HOST_API void* lantern_gelu_tensor(void* self) { void* ret = _lantern_gelu_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gelu_backward_tensor_tensor)(void* grad, void* self);
  HOST_API void* lantern_gelu_backward_tensor_tensor(void* grad, void* self) { void* ret = _lantern_gelu_backward_tensor_tensor(grad, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardshrink_tensor_scalar)(void* self, void* lambd);
  HOST_API void* lantern_hardshrink_tensor_scalar(void* self, void* lambd) { void* ret = _lantern_hardshrink_tensor_scalar(self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_hardshrink_tensor_scalar)(void* self, void* lambd);
  HOST_API void* lantern_Tensor_hardshrink_tensor_scalar(void* self, void* lambd) { void* ret = _lantern_Tensor_hardshrink_tensor_scalar(self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardshrink_backward_tensor_tensor_scalar)(void* grad_out, void* self, void* lambd);
  HOST_API void* lantern_hardshrink_backward_tensor_tensor_scalar(void* grad_out, void* self, void* lambd) { void* ret = _lantern_hardshrink_backward_tensor_tensor_scalar(grad_out, self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_hardshrink_backward_tensor_tensor_scalar)(void* grad_out, void* self, void* lambd);
  HOST_API void* lantern_Tensor_hardshrink_backward_tensor_tensor_scalar(void* grad_out, void* self, void* lambd) { void* ret = _lantern_Tensor_hardshrink_backward_tensor_tensor_scalar(grad_out, self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rsqrt_tensor)(void* self);
  HOST_API void* lantern_rsqrt_tensor(void* self) { void* ret = _lantern_rsqrt_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rsqrt_tensor)(void* self);
  HOST_API void* lantern_Tensor_rsqrt_tensor(void* self) { void* ret = _lantern_Tensor_rsqrt_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rsqrt__tensor)(void* self);
  HOST_API void* lantern_rsqrt__tensor(void* self) { void* ret = _lantern_rsqrt__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rsqrt__tensor)(void* self);
  HOST_API void* lantern_Tensor_rsqrt__tensor(void* self) { void* ret = _lantern_Tensor_rsqrt__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rsqrt_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_rsqrt_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_rsqrt_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_select_tensor_dimname_intt)(void* self, void* dim, void* index);
  HOST_API void* lantern_select_tensor_dimname_intt(void* self, void* dim, void* index) { void* ret = _lantern_select_tensor_dimname_intt(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_select_tensor_dimname_intt)(void* self, void* dim, void* index);
  HOST_API void* lantern_Tensor_select_tensor_dimname_intt(void* self, void* dim, void* index) { void* ret = _lantern_Tensor_select_tensor_dimname_intt(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_select_tensor_intt_intt)(void* self, void* dim, void* index);
  HOST_API void* lantern_select_tensor_intt_intt(void* self, void* dim, void* index) { void* ret = _lantern_select_tensor_intt_intt(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_select_tensor_intt_intt)(void* self, void* dim, void* index);
  HOST_API void* lantern_Tensor_select_tensor_intt_intt(void* self, void* dim, void* index) { void* ret = _lantern_Tensor_select_tensor_intt_intt(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_selu_tensor)(void* self);
  HOST_API void* lantern_selu_tensor(void* self) { void* ret = _lantern_selu_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_selu__tensor)(void* self);
  HOST_API void* lantern_selu__tensor(void* self) { void* ret = _lantern_selu__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_celu_tensor_scalar)(void* self, void* alpha);
  HOST_API void* lantern_celu_tensor_scalar(void* self, void* alpha) { void* ret = _lantern_celu_tensor_scalar(self, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_celu__tensor_scalar)(void* self, void* alpha);
  HOST_API void* lantern_celu__tensor_scalar(void* self, void* alpha) { void* ret = _lantern_celu__tensor_scalar(self, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sigmoid_tensor)(void* self);
  HOST_API void* lantern_sigmoid_tensor(void* self) { void* ret = _lantern_sigmoid_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sigmoid_tensor)(void* self);
  HOST_API void* lantern_Tensor_sigmoid_tensor(void* self) { void* ret = _lantern_Tensor_sigmoid_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sigmoid__tensor)(void* self);
  HOST_API void* lantern_sigmoid__tensor(void* self) { void* ret = _lantern_sigmoid__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sigmoid__tensor)(void* self);
  HOST_API void* lantern_Tensor_sigmoid__tensor(void* self) { void* ret = _lantern_Tensor_sigmoid__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sigmoid_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_sigmoid_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_sigmoid_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sin_tensor)(void* self);
  HOST_API void* lantern_sin_tensor(void* self) { void* ret = _lantern_sin_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sin_tensor)(void* self);
  HOST_API void* lantern_Tensor_sin_tensor(void* self) { void* ret = _lantern_Tensor_sin_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sin__tensor)(void* self);
  HOST_API void* lantern_sin__tensor(void* self) { void* ret = _lantern_sin__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sin__tensor)(void* self);
  HOST_API void* lantern_Tensor_sin__tensor(void* self) { void* ret = _lantern_Tensor_sin__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sin_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_sin_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_sin_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sinh_tensor)(void* self);
  HOST_API void* lantern_sinh_tensor(void* self) { void* ret = _lantern_sinh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sinh_tensor)(void* self);
  HOST_API void* lantern_Tensor_sinh_tensor(void* self) { void* ret = _lantern_Tensor_sinh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sinh__tensor)(void* self);
  HOST_API void* lantern_sinh__tensor(void* self) { void* ret = _lantern_sinh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sinh__tensor)(void* self);
  HOST_API void* lantern_Tensor_sinh__tensor(void* self) { void* ret = _lantern_Tensor_sinh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sinh_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_sinh_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_sinh_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_detach_tensor)(void* self);
  HOST_API void* lantern_detach_tensor(void* self) { void* ret = _lantern_detach_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_detach_tensor)(void* self);
  HOST_API void* lantern_Tensor_detach_tensor(void* self) { void* ret = _lantern_Tensor_detach_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_detach__tensor)(void* self);
  HOST_API void* lantern_detach__tensor(void* self) { void* ret = _lantern_detach__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_detach__tensor)(void* self);
  HOST_API void* lantern_Tensor_detach__tensor(void* self) { void* ret = _lantern_Tensor_detach__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_size_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_size_tensor_intt(void* self, void* dim) { void* ret = _lantern_size_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_size_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_size_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_size_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_size_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_size_tensor_dimname(void* self, void* dim) { void* ret = _lantern_size_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_size_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_size_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_size_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slice_tensor_intt_intt_intt_intt)(void* self, void* dim, void* start, void* end, void* step);
  HOST_API void* lantern_slice_tensor_intt_intt_intt_intt(void* self, void* dim, void* start, void* end, void* step) { void* ret = _lantern_slice_tensor_intt_intt_intt_intt(self, dim, start, end, step); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_slice_tensor_intt_intt_intt_intt)(void* self, void* dim, void* start, void* end, void* step);
  HOST_API void* lantern_Tensor_slice_tensor_intt_intt_intt_intt(void* self, void* dim, void* start, void* end, void* step) { void* ret = _lantern_Tensor_slice_tensor_intt_intt_intt_intt(self, dim, start, end, step); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slogdet_tensor)(void* self);
  HOST_API void* lantern_slogdet_tensor(void* self) { void* ret = _lantern_slogdet_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_slogdet_tensor)(void* self);
  HOST_API void* lantern_Tensor_slogdet_tensor(void* self) { void* ret = _lantern_Tensor_slogdet_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_smm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_smm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_smm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_smm_tensor_tensor)(void* self, void* mat2);
  HOST_API void* lantern_Tensor_smm_tensor_tensor(void* self, void* mat2) { void* ret = _lantern_Tensor_smm_tensor_tensor(self, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softmax_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_softmax_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_softmax_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_softmax_tensor_intt_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_softmax_tensor_intt_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_softmax_tensor_intt_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softmax_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_softmax_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_softmax_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_softmax_tensor_dimname_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern_Tensor_softmax_tensor_dimname_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern_Tensor_softmax_tensor_dimname_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__softmax_tensor_intt_bool)(void* self, void* dim, void* half_to_float);
  HOST_API void* lantern__softmax_tensor_intt_bool(void* self, void* dim, void* half_to_float) { void* ret = _lantern__softmax_tensor_intt_bool(self, dim, half_to_float); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__softmax_backward_data_tensor_tensor_intt_tensor)(void* grad_output, void* output, void* dim, void* self);
  HOST_API void* lantern__softmax_backward_data_tensor_tensor_intt_tensor(void* grad_output, void* output, void* dim, void* self) { void* ret = _lantern__softmax_backward_data_tensor_tensor_intt_tensor(grad_output, output, dim, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_split_tensor_intt_intt)(void* self, void* split_size, void* dim);
  HOST_API void* lantern_split_tensor_intt_intt(void* self, void* split_size, void* dim) { void* ret = _lantern_split_tensor_intt_intt(self, split_size, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_split_tensor_intt_intt)(void* self, void* split_size, void* dim);
  HOST_API void* lantern_Tensor_split_tensor_intt_intt(void* self, void* split_size, void* dim) { void* ret = _lantern_Tensor_split_tensor_intt_intt(self, split_size, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_split_with_sizes_tensor_intarrayref_intt)(void* self, void* split_sizes, void* dim);
  HOST_API void* lantern_split_with_sizes_tensor_intarrayref_intt(void* self, void* split_sizes, void* dim) { void* ret = _lantern_split_with_sizes_tensor_intarrayref_intt(self, split_sizes, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_split_with_sizes_tensor_intarrayref_intt)(void* self, void* split_sizes, void* dim);
  HOST_API void* lantern_Tensor_split_with_sizes_tensor_intarrayref_intt(void* self, void* split_sizes, void* dim) { void* ret = _lantern_Tensor_split_with_sizes_tensor_intarrayref_intt(self, split_sizes, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_squeeze_tensor)(void* self);
  HOST_API void* lantern_squeeze_tensor(void* self) { void* ret = _lantern_squeeze_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze_tensor)(void* self);
  HOST_API void* lantern_Tensor_squeeze_tensor(void* self) { void* ret = _lantern_Tensor_squeeze_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_squeeze_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_squeeze_tensor_intt(void* self, void* dim) { void* ret = _lantern_squeeze_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_squeeze_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_squeeze_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_squeeze_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_squeeze_tensor_dimname(void* self, void* dim) { void* ret = _lantern_squeeze_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_squeeze_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_squeeze_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze__tensor)(void* self);
  HOST_API void* lantern_Tensor_squeeze__tensor(void* self) { void* ret = _lantern_Tensor_squeeze__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze__tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_squeeze__tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_squeeze__tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_squeeze__tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_squeeze__tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_squeeze__tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sspaddmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_sspaddmm_tensor_tensor_tensor_scalar_scalar(void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_sspaddmm_tensor_tensor_tensor_scalar_scalar(self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sspaddmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_sspaddmm_tensor_tensor_tensor_scalar_scalar(void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_Tensor_sspaddmm_tensor_tensor_tensor_scalar_scalar(self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sspaddmm_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_sspaddmm_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_sspaddmm_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_stack_tensorlist_intt)(void* tensors, void* dim);
  HOST_API void* lantern_stack_tensorlist_intt(void* tensors, void* dim) { void* ret = _lantern_stack_tensorlist_intt(tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_stack_out_tensor_tensorlist_intt)(void* out, void* tensors, void* dim);
  HOST_API void* lantern_stack_out_tensor_tensorlist_intt(void* out, void* tensors, void* dim) { void* ret = _lantern_stack_out_tensor_tensorlist_intt(out, tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_stft_tensor_intt_intt_intt_tensor_bool_bool)(void* self, void* n_fft, void* hop_length, void* win_length, void* window, void* normalized, void* onesided);
  HOST_API void* lantern_stft_tensor_intt_intt_intt_tensor_bool_bool(void* self, void* n_fft, void* hop_length, void* win_length, void* window, void* normalized, void* onesided) { void* ret = _lantern_stft_tensor_intt_intt_intt_tensor_bool_bool(self, n_fft, hop_length, win_length, window, normalized, onesided); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_stft_tensor_intt_intt_intt_tensor_bool_bool)(void* self, void* n_fft, void* hop_length, void* win_length, void* window, void* normalized, void* onesided);
  HOST_API void* lantern_Tensor_stft_tensor_intt_intt_intt_tensor_bool_bool(void* self, void* n_fft, void* hop_length, void* win_length, void* window, void* normalized, void* onesided) { void* ret = _lantern_Tensor_stft_tensor_intt_intt_intt_tensor_bool_bool(self, n_fft, hop_length, win_length, window, normalized, onesided); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_stride_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_stride_tensor_intt(void* self, void* dim) { void* ret = _lantern_stride_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_stride_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_stride_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_stride_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_stride_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_stride_tensor_dimname(void* self, void* dim) { void* ret = _lantern_stride_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_stride_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_stride_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_stride_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sum_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_sum_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_sum_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sum_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_Tensor_sum_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_Tensor_sum_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sum_tensor_intarrayref_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_sum_tensor_intarrayref_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_sum_tensor_intarrayref_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sum_tensor_intarrayref_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_sum_tensor_intarrayref_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_sum_tensor_intarrayref_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sum_tensor_dimnamelist_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_sum_tensor_dimnamelist_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_sum_tensor_dimnamelist_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sum_tensor_dimnamelist_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_sum_tensor_dimnamelist_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_sum_tensor_dimnamelist_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sum_out_tensor_tensor_intarrayref_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_sum_out_tensor_tensor_intarrayref_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_sum_out_tensor_tensor_intarrayref_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sum_out_tensor_tensor_dimnamelist_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_sum_out_tensor_tensor_dimnamelist_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_sum_out_tensor_tensor_dimnamelist_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sum_to_size_tensor_intarrayref)(void* self, void* size);
  HOST_API void* lantern_Tensor_sum_to_size_tensor_intarrayref(void* self, void* size) { void* ret = _lantern_Tensor_sum_to_size_tensor_intarrayref(self, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sqrt_tensor)(void* self);
  HOST_API void* lantern_sqrt_tensor(void* self) { void* ret = _lantern_sqrt_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sqrt_tensor)(void* self);
  HOST_API void* lantern_Tensor_sqrt_tensor(void* self) { void* ret = _lantern_Tensor_sqrt_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sqrt__tensor)(void* self);
  HOST_API void* lantern_sqrt__tensor(void* self) { void* ret = _lantern_sqrt__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sqrt__tensor)(void* self);
  HOST_API void* lantern_Tensor_sqrt__tensor(void* self) { void* ret = _lantern_Tensor_sqrt__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sqrt_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_sqrt_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_sqrt_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_square_tensor)(void* self);
  HOST_API void* lantern_square_tensor(void* self) { void* ret = _lantern_square_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_square_tensor)(void* self);
  HOST_API void* lantern_Tensor_square_tensor(void* self) { void* ret = _lantern_Tensor_square_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_square__tensor)(void* self);
  HOST_API void* lantern_square__tensor(void* self) { void* ret = _lantern_square__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_square__tensor)(void* self);
  HOST_API void* lantern_Tensor_square__tensor(void* self) { void* ret = _lantern_Tensor_square__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_std_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_std_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_std_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_Tensor_std_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_Tensor_std_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_std_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_Tensor_std_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_Tensor_std_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_mean_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_std_mean_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_std_mean_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_mean_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_mean_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_mean_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_mean_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_mean_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_mean_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_out_tensor_tensor_intarrayref_bool_bool)(void* out, void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_out_tensor_tensor_intarrayref_bool_bool(void* out, void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_out_tensor_tensor_intarrayref_bool_bool(out, self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_std_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_Tensor_std_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_Tensor_std_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_std_out_tensor_tensor_dimnamelist_bool_bool)(void* out, void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_std_out_tensor_tensor_dimnamelist_bool_bool(void* out, void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_std_out_tensor_tensor_dimnamelist_bool_bool(out, self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prod_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_prod_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_prod_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_prod_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern_Tensor_prod_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern_Tensor_prod_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prod_tensor_intt_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_prod_tensor_intt_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_prod_tensor_intt_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_prod_tensor_intt_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_prod_tensor_intt_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_prod_tensor_intt_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prod_out_tensor_tensor_intt_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_prod_out_tensor_tensor_intt_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_prod_out_tensor_tensor_intt_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prod_tensor_dimname_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_prod_tensor_dimname_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_prod_tensor_dimname_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_prod_tensor_dimname_bool_scalartype)(void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_prod_tensor_dimname_bool_scalartype(void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_prod_tensor_dimname_bool_scalartype(self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_prod_out_tensor_tensor_dimname_bool_scalartype)(void* out, void* self, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_prod_out_tensor_tensor_dimname_bool_scalartype(void* out, void* self, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_prod_out_tensor_tensor_dimname_bool_scalartype(out, self, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_t_tensor)(void* self);
  HOST_API void* lantern_t_tensor(void* self) { void* ret = _lantern_t_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_t_tensor)(void* self);
  HOST_API void* lantern_Tensor_t_tensor(void* self) { void* ret = _lantern_Tensor_t_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_t__tensor)(void* self);
  HOST_API void* lantern_Tensor_t__tensor(void* self) { void* ret = _lantern_Tensor_t__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tan_tensor)(void* self);
  HOST_API void* lantern_tan_tensor(void* self) { void* ret = _lantern_tan_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tan_tensor)(void* self);
  HOST_API void* lantern_Tensor_tan_tensor(void* self) { void* ret = _lantern_Tensor_tan_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tan__tensor)(void* self);
  HOST_API void* lantern_tan__tensor(void* self) { void* ret = _lantern_tan__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tan__tensor)(void* self);
  HOST_API void* lantern_Tensor_tan__tensor(void* self) { void* ret = _lantern_Tensor_tan__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tan_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_tan_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_tan_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tanh_tensor)(void* self);
  HOST_API void* lantern_tanh_tensor(void* self) { void* ret = _lantern_tanh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tanh_tensor)(void* self);
  HOST_API void* lantern_Tensor_tanh_tensor(void* self) { void* ret = _lantern_Tensor_tanh_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tanh__tensor)(void* self);
  HOST_API void* lantern_tanh__tensor(void* self) { void* ret = _lantern_tanh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tanh__tensor)(void* self);
  HOST_API void* lantern_Tensor_tanh__tensor(void* self) { void* ret = _lantern_Tensor_tanh__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tanh_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_tanh_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_tanh_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tensordot_tensor_tensor_intarrayref_intarrayref)(void* self, void* other, void* dims_self, void* dims_other);
  HOST_API void* lantern_tensordot_tensor_tensor_intarrayref_intarrayref(void* self, void* other, void* dims_self, void* dims_other) { void* ret = _lantern_tensordot_tensor_tensor_intarrayref_intarrayref(self, other, dims_self, dims_other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_threshold_tensor_scalar_scalar)(void* self, void* threshold, void* value);
  HOST_API void* lantern_threshold_tensor_scalar_scalar(void* self, void* threshold, void* value) { void* ret = _lantern_threshold_tensor_scalar_scalar(self, threshold, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_threshold__tensor_scalar_scalar)(void* self, void* threshold, void* value);
  HOST_API void* lantern_threshold__tensor_scalar_scalar(void* self, void* threshold, void* value) { void* ret = _lantern_threshold__tensor_scalar_scalar(self, threshold, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_threshold_out_tensor_tensor_scalar_scalar)(void* out, void* self, void* threshold, void* value);
  HOST_API void* lantern_threshold_out_tensor_tensor_scalar_scalar(void* out, void* self, void* threshold, void* value) { void* ret = _lantern_threshold_out_tensor_tensor_scalar_scalar(out, self, threshold, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_threshold_backward_tensor_tensor_scalar)(void* grad_output, void* self, void* threshold);
  HOST_API void* lantern_threshold_backward_tensor_tensor_scalar(void* grad_output, void* self, void* threshold) { void* ret = _lantern_threshold_backward_tensor_tensor_scalar(grad_output, self, threshold); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_transpose_tensor_intt_intt)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern_transpose_tensor_intt_intt(void* self, void* dim0, void* dim1) { void* ret = _lantern_transpose_tensor_intt_intt(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_transpose_tensor_intt_intt)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern_Tensor_transpose_tensor_intt_intt(void* self, void* dim0, void* dim1) { void* ret = _lantern_Tensor_transpose_tensor_intt_intt(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_transpose_tensor_dimname_dimname)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern_transpose_tensor_dimname_dimname(void* self, void* dim0, void* dim1) { void* ret = _lantern_transpose_tensor_dimname_dimname(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_transpose_tensor_dimname_dimname)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern_Tensor_transpose_tensor_dimname_dimname(void* self, void* dim0, void* dim1) { void* ret = _lantern_Tensor_transpose_tensor_dimname_dimname(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__mkldnn_transpose_tensor_intt_intt)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern__mkldnn_transpose_tensor_intt_intt(void* self, void* dim0, void* dim1) { void* ret = _lantern__mkldnn_transpose_tensor_intt_intt(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_transpose__tensor_intt_intt)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern_Tensor_transpose__tensor_intt_intt(void* self, void* dim0, void* dim1) { void* ret = _lantern_Tensor_transpose__tensor_intt_intt(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__mkldnn_transpose__tensor_intt_intt)(void* self, void* dim0, void* dim1);
  HOST_API void* lantern__mkldnn_transpose__tensor_intt_intt(void* self, void* dim0, void* dim1) { void* ret = _lantern__mkldnn_transpose__tensor_intt_intt(self, dim0, dim1); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_one_hot_tensor_intt)(void* self, void* num_classes);
  HOST_API void* lantern_one_hot_tensor_intt(void* self, void* num_classes) { void* ret = _lantern_one_hot_tensor_intt(self, num_classes); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_flip_tensor_intarrayref)(void* self, void* dims);
  HOST_API void* lantern_flip_tensor_intarrayref(void* self, void* dims) { void* ret = _lantern_flip_tensor_intarrayref(self, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_flip_tensor_intarrayref)(void* self, void* dims);
  HOST_API void* lantern_Tensor_flip_tensor_intarrayref(void* self, void* dims) { void* ret = _lantern_Tensor_flip_tensor_intarrayref(self, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_roll_tensor_intarrayref_intarrayref)(void* self, void* shifts, void* dims);
  HOST_API void* lantern_roll_tensor_intarrayref_intarrayref(void* self, void* shifts, void* dims) { void* ret = _lantern_roll_tensor_intarrayref_intarrayref(self, shifts, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_roll_tensor_intarrayref_intarrayref)(void* self, void* shifts, void* dims);
  HOST_API void* lantern_Tensor_roll_tensor_intarrayref_intarrayref(void* self, void* shifts, void* dims) { void* ret = _lantern_Tensor_roll_tensor_intarrayref_intarrayref(self, shifts, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rot90_tensor_intt_intarrayref)(void* self, void* k, void* dims);
  HOST_API void* lantern_rot90_tensor_intt_intarrayref(void* self, void* k, void* dims) { void* ret = _lantern_rot90_tensor_intt_intarrayref(self, k, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_rot90_tensor_intt_intarrayref)(void* self, void* k, void* dims);
  HOST_API void* lantern_Tensor_rot90_tensor_intt_intarrayref(void* self, void* k, void* dims) { void* ret = _lantern_Tensor_rot90_tensor_intt_intarrayref(self, k, dims); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trapz_tensor_tensor_intt)(void* y, void* x, void* dim);
  HOST_API void* lantern_trapz_tensor_tensor_intt(void* y, void* x, void* dim) { void* ret = _lantern_trapz_tensor_tensor_intt(y, x, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trapz_tensor_double_intt)(void* y, void* dx, void* dim);
  HOST_API void* lantern_trapz_tensor_double_intt(void* y, void* dx, void* dim) { void* ret = _lantern_trapz_tensor_double_intt(y, dx, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__trilinear_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt)(void* i1, void* i2, void* i3, void* expand1, void* expand2, void* expand3, void* sumdim, void* unroll_dim);
  HOST_API void* lantern__trilinear_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt(void* i1, void* i2, void* i3, void* expand1, void* expand2, void* expand3, void* sumdim, void* unroll_dim) { void* ret = _lantern__trilinear_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt(i1, i2, i3, expand1, expand2, expand3, sumdim, unroll_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triplet_margin_loss_tensor_tensor_tensor_double_double_double_bool_intt)(void* anchor, void* positive, void* negative, void* margin, void* p, void* eps, void* swap, void* reduction);
  HOST_API void* lantern_triplet_margin_loss_tensor_tensor_tensor_double_double_double_bool_intt(void* anchor, void* positive, void* negative, void* margin, void* p, void* eps, void* swap, void* reduction) { void* ret = _lantern_triplet_margin_loss_tensor_tensor_tensor_double_double_double_bool_intt(anchor, positive, negative, margin, p, eps, swap, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_true_divide_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_true_divide_tensor_tensor(void* self, void* other) { void* ret = _lantern_true_divide_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_true_divide_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_true_divide_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_true_divide_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_true_divide__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_true_divide__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_true_divide__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_true_divide_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_true_divide_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_true_divide_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_true_divide_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_true_divide_tensor_scalar(void* self, void* other) { void* ret = _lantern_true_divide_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_true_divide_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_true_divide_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_true_divide_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_true_divide__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_true_divide__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_true_divide__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trunc_tensor)(void* self);
  HOST_API void* lantern_trunc_tensor(void* self) { void* ret = _lantern_trunc_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_trunc_tensor)(void* self);
  HOST_API void* lantern_Tensor_trunc_tensor(void* self) { void* ret = _lantern_Tensor_trunc_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trunc__tensor)(void* self);
  HOST_API void* lantern_trunc__tensor(void* self) { void* ret = _lantern_trunc__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_trunc__tensor)(void* self);
  HOST_API void* lantern_Tensor_trunc__tensor(void* self) { void* ret = _lantern_Tensor_trunc__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trunc_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_trunc_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_trunc_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_type_as_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_type_as_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_type_as_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__has_compatible_shallow_copy_type_tensor_tensor)(void* self, void* from);
  HOST_API void* lantern__has_compatible_shallow_copy_type_tensor_tensor(void* self, void* from) { void* ret = _lantern__has_compatible_shallow_copy_type_tensor_tensor(self, from); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__unique_tensor_bool_bool)(void* self, void* sorted, void* return_inverse);
  HOST_API void* lantern__unique_tensor_bool_bool(void* self, void* sorted, void* return_inverse) { void* ret = _lantern__unique_tensor_bool_bool(self, sorted, return_inverse); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unique_dim_tensor_intt_bool_bool_bool)(void* self, void* dim, void* sorted, void* return_inverse, void* return_counts);
  HOST_API void* lantern_unique_dim_tensor_intt_bool_bool_bool(void* self, void* dim, void* sorted, void* return_inverse, void* return_counts) { void* ret = _lantern_unique_dim_tensor_intt_bool_bool_bool(self, dim, sorted, return_inverse, return_counts); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unique_consecutive_tensor_bool_bool_intt)(void* self, void* return_inverse, void* return_counts, void* dim);
  HOST_API void* lantern_unique_consecutive_tensor_bool_bool_intt(void* self, void* return_inverse, void* return_counts, void* dim) { void* ret = _lantern_unique_consecutive_tensor_bool_bool_intt(self, return_inverse, return_counts, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unique_dim_consecutive_tensor_intt_bool_bool)(void* self, void* dim, void* return_inverse, void* return_counts);
  HOST_API void* lantern_unique_dim_consecutive_tensor_intt_bool_bool(void* self, void* dim, void* return_inverse, void* return_counts) { void* ret = _lantern_unique_dim_consecutive_tensor_intt_bool_bool(self, dim, return_inverse, return_counts); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__unique2_tensor_bool_bool_bool)(void* self, void* sorted, void* return_inverse, void* return_counts);
  HOST_API void* lantern__unique2_tensor_bool_bool_bool(void* self, void* sorted, void* return_inverse, void* return_counts) { void* ret = _lantern__unique2_tensor_bool_bool_bool(self, sorted, return_inverse, return_counts); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__unsafe_view_tensor_intarrayref)(void* self, void* size);
  HOST_API void* lantern__unsafe_view_tensor_intarrayref(void* self, void* size) { void* ret = _lantern__unsafe_view_tensor_intarrayref(self, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unsqueeze_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_unsqueeze_tensor_intt(void* self, void* dim) { void* ret = _lantern_unsqueeze_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unsqueeze_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_unsqueeze_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_unsqueeze_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unsqueeze__tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_unsqueeze__tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_unsqueeze__tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_var_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_var_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_var_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_Tensor_var_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_Tensor_var_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_var_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_Tensor_var_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_Tensor_var_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_out_tensor_tensor_intarrayref_bool_bool)(void* out, void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_out_tensor_tensor_intarrayref_bool_bool(void* out, void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_out_tensor_tensor_intarrayref_bool_bool(out, self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_var_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_Tensor_var_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_Tensor_var_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_out_tensor_tensor_dimnamelist_bool_bool)(void* out, void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_out_tensor_tensor_dimnamelist_bool_bool(void* out, void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_out_tensor_tensor_dimnamelist_bool_bool(out, self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_mean_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern_var_mean_tensor_bool(void* self, void* unbiased) { void* ret = _lantern_var_mean_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_mean_tensor_intarrayref_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_mean_tensor_intarrayref_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_mean_tensor_intarrayref_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_var_mean_tensor_dimnamelist_bool_bool)(void* self, void* dim, void* unbiased, void* keepdim);
  HOST_API void* lantern_var_mean_tensor_dimnamelist_bool_bool(void* self, void* dim, void* unbiased, void* keepdim) { void* ret = _lantern_var_mean_tensor_dimnamelist_bool_bool(self, dim, unbiased, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_view_as_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_view_as_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_view_as_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_where_tensor_tensor_tensor)(void* condition, void* self, void* other);
  HOST_API void* lantern_where_tensor_tensor_tensor(void* condition, void* self, void* other) { void* ret = _lantern_where_tensor_tensor_tensor(condition, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_where_tensor_tensor_tensor)(void* condition, void* self, void* other);
  HOST_API void* lantern_Tensor_where_tensor_tensor_tensor(void* condition, void* self, void* other) { void* ret = _lantern_Tensor_where_tensor_tensor_tensor(condition, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_where_tensor)(void* condition);
  HOST_API void* lantern_where_tensor(void* condition) { void* ret = _lantern_where_tensor(condition); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__s_where_tensor_tensor_tensor)(void* condition, void* self, void* other);
  HOST_API void* lantern__s_where_tensor_tensor_tensor(void* condition, void* self, void* other) { void* ret = _lantern__s_where_tensor_tensor_tensor(condition, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_except_dim_tensor_intt_intt)(void* v, void* pow, void* dim);
  HOST_API void* lantern_norm_except_dim_tensor_intt_intt(void* v, void* pow, void* dim) { void* ret = _lantern_norm_except_dim_tensor_intt_intt(v, pow, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__weight_norm_tensor_tensor_intt)(void* v, void* g, void* dim);
  HOST_API void* lantern__weight_norm_tensor_tensor_intt(void* v, void* g, void* dim) { void* ret = _lantern__weight_norm_tensor_tensor_intt(v, g, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__weight_norm_cuda_interface_tensor_tensor_intt)(void* v, void* g, void* dim);
  HOST_API void* lantern__weight_norm_cuda_interface_tensor_tensor_intt(void* v, void* g, void* dim) { void* ret = _lantern__weight_norm_cuda_interface_tensor_tensor_intt(v, g, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__weight_norm_cuda_interface_backward_tensor_tensor_tensor_tensor_intt)(void* grad_w, void* saved_v, void* saved_g, void* saved_norms, void* dim);
  HOST_API void* lantern__weight_norm_cuda_interface_backward_tensor_tensor_tensor_tensor_intt(void* grad_w, void* saved_v, void* saved_g, void* saved_norms, void* dim) { void* ret = _lantern__weight_norm_cuda_interface_backward_tensor_tensor_tensor_tensor_intt(grad_w, saved_v, saved_g, saved_norms, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__weight_norm_differentiable_backward_tensor_tensor_tensor_tensor_intt)(void* grad_w, void* saved_v, void* saved_g, void* saved_norms, void* dim);
  HOST_API void* lantern__weight_norm_differentiable_backward_tensor_tensor_tensor_tensor_intt(void* grad_w, void* saved_v, void* saved_g, void* saved_norms, void* dim) { void* ret = _lantern__weight_norm_differentiable_backward_tensor_tensor_tensor_tensor_intt(grad_w, saved_v, saved_g, saved_norms, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_zeros_intarrayref_dimnamelist_tensoroptions)(void* size, void* names, void* options);
  HOST_API void* lantern_zeros_intarrayref_dimnamelist_tensoroptions(void* size, void* names, void* options) { void* ret = _lantern_zeros_intarrayref_dimnamelist_tensoroptions(size, names, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_zeros_intarrayref_tensoroptions)(void* size, void* options);
  HOST_API void* lantern_zeros_intarrayref_tensoroptions(void* size, void* options) { void* ret = _lantern_zeros_intarrayref_tensoroptions(size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_zeros_out_tensor_intarrayref)(void* out, void* size);
  HOST_API void* lantern_zeros_out_tensor_intarrayref(void* out, void* size) { void* ret = _lantern_zeros_out_tensor_intarrayref(out, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_zeros_like_tensor_tensoroptions_memoryformat)(void* self, void* options, void* memory_format);
  HOST_API void* lantern_zeros_like_tensor_tensoroptions_memoryformat(void* self, void* options, void* memory_format) { void* ret = _lantern_zeros_like_tensor_tensoroptions_memoryformat(self, options, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__standard_gamma_grad_tensor_tensor)(void* self, void* output);
  HOST_API void* lantern__standard_gamma_grad_tensor_tensor(void* self, void* output) { void* ret = _lantern__standard_gamma_grad_tensor_tensor(self, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__standard_gamma_tensor_generator)(void* self, void* generator);
  HOST_API void* lantern__standard_gamma_tensor_generator(void* self, void* generator) { void* ret = _lantern__standard_gamma_tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__dirichlet_grad_tensor_tensor_tensor)(void* x, void* alpha, void* total);
  HOST_API void* lantern__dirichlet_grad_tensor_tensor_tensor(void* x, void* alpha, void* total) { void* ret = _lantern__dirichlet_grad_tensor_tensor_tensor(x, alpha, total); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sample_dirichlet_tensor_generator)(void* self, void* generator);
  HOST_API void* lantern__sample_dirichlet_tensor_generator(void* self, void* generator) { void* ret = _lantern__sample_dirichlet_tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_poisson_tensor_generator)(void* self, void* generator);
  HOST_API void* lantern_poisson_tensor_generator(void* self, void* generator) { void* ret = _lantern_poisson_tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_native_norm_tensor_scalar)(void* self, void* p);
  HOST_API void* lantern_native_norm_tensor_scalar(void* self, void* p) { void* ret = _lantern_native_norm_tensor_scalar(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_sum_tensor)(void* self);
  HOST_API void* lantern__sparse_sum_tensor(void* self) { void* ret = _lantern__sparse_sum_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_sum_tensor_scalartype)(void* self, void* dtype);
  HOST_API void* lantern__sparse_sum_tensor_scalartype(void* self, void* dtype) { void* ret = _lantern__sparse_sum_tensor_scalartype(self, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_sum_tensor_intarrayref)(void* self, void* dim);
  HOST_API void* lantern__sparse_sum_tensor_intarrayref(void* self, void* dim) { void* ret = _lantern__sparse_sum_tensor_intarrayref(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_sum_tensor_intarrayref_scalartype)(void* self, void* dim, void* dtype);
  HOST_API void* lantern__sparse_sum_tensor_intarrayref_scalartype(void* self, void* dim, void* dtype) { void* ret = _lantern__sparse_sum_tensor_intarrayref_scalartype(self, dim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_sum_backward_tensor_tensor_intarrayref)(void* grad, void* self, void* dim);
  HOST_API void* lantern__sparse_sum_backward_tensor_tensor_intarrayref(void* grad, void* self, void* dim) { void* ret = _lantern__sparse_sum_backward_tensor_tensor_intarrayref(grad, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar_scalartype)(void* self, void* p, void* dtype);
  HOST_API void* lantern_norm_tensor_scalar_scalartype(void* self, void* p, void* dtype) { void* ret = _lantern_norm_tensor_scalar_scalartype(self, p, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar_scalartype)(void* self, void* p, void* dtype);
  HOST_API void* lantern_Tensor_norm_tensor_scalar_scalartype(void* self, void* p, void* dtype) { void* ret = _lantern_Tensor_norm_tensor_scalar_scalartype(self, p, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar)(void* self, void* p);
  HOST_API void* lantern_norm_tensor_scalar(void* self, void* p) { void* ret = _lantern_norm_tensor_scalar(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar)(void* self, void* p);
  HOST_API void* lantern_Tensor_norm_tensor_scalar(void* self, void* p) { void* ret = _lantern_Tensor_norm_tensor_scalar(self, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar_intarrayref_bool_scalartype)(void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_norm_tensor_scalar_intarrayref_bool_scalartype(void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_norm_tensor_scalar_intarrayref_bool_scalartype(self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar_intarrayref_bool_scalartype)(void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_norm_tensor_scalar_intarrayref_bool_scalartype(void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_norm_tensor_scalar_intarrayref_bool_scalartype(self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar_intarrayref_bool)(void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_norm_tensor_scalar_intarrayref_bool(void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_norm_tensor_scalar_intarrayref_bool(self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar_intarrayref_bool)(void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_norm_tensor_scalar_intarrayref_bool(void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_Tensor_norm_tensor_scalar_intarrayref_bool(self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_out_tensor_tensor_scalar_intarrayref_bool_scalartype)(void* out, void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_norm_out_tensor_tensor_scalar_intarrayref_bool_scalartype(void* out, void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_norm_out_tensor_tensor_scalar_intarrayref_bool_scalartype(out, self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_out_tensor_tensor_scalar_intarrayref_bool)(void* out, void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_norm_out_tensor_tensor_scalar_intarrayref_bool(void* out, void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_norm_out_tensor_tensor_scalar_intarrayref_bool(out, self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar_dimnamelist_bool_scalartype)(void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_norm_tensor_scalar_dimnamelist_bool_scalartype(void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_norm_tensor_scalar_dimnamelist_bool_scalartype(self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar_dimnamelist_bool_scalartype)(void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_Tensor_norm_tensor_scalar_dimnamelist_bool_scalartype(void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_Tensor_norm_tensor_scalar_dimnamelist_bool_scalartype(self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_tensor_scalar_dimnamelist_bool)(void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_norm_tensor_scalar_dimnamelist_bool(void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_norm_tensor_scalar_dimnamelist_bool(self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_norm_tensor_scalar_dimnamelist_bool)(void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_Tensor_norm_tensor_scalar_dimnamelist_bool(void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_Tensor_norm_tensor_scalar_dimnamelist_bool(self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool_scalartype)(void* out, void* self, void* p, void* dim, void* keepdim, void* dtype);
  HOST_API void* lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool_scalartype(void* out, void* self, void* p, void* dim, void* keepdim, void* dtype) { void* ret = _lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool_scalartype(out, self, p, dim, keepdim, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool)(void* out, void* self, void* p, void* dim, void* keepdim);
  HOST_API void* lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool(void* out, void* self, void* p, void* dim, void* keepdim) { void* ret = _lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool(out, self, p, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frobenius_norm_tensor)(void* self);
  HOST_API void* lantern_frobenius_norm_tensor(void* self) { void* ret = _lantern_frobenius_norm_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frobenius_norm_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_frobenius_norm_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_frobenius_norm_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_frobenius_norm_out_tensor_tensor_intarrayref_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_frobenius_norm_out_tensor_tensor_intarrayref_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_frobenius_norm_out_tensor_tensor_intarrayref_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nuclear_norm_tensor_bool)(void* self, void* keepdim);
  HOST_API void* lantern_nuclear_norm_tensor_bool(void* self, void* keepdim) { void* ret = _lantern_nuclear_norm_tensor_bool(self, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nuclear_norm_out_tensor_tensor_bool)(void* out, void* self, void* keepdim);
  HOST_API void* lantern_nuclear_norm_out_tensor_tensor_bool(void* out, void* self, void* keepdim) { void* ret = _lantern_nuclear_norm_out_tensor_tensor_bool(out, self, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nuclear_norm_tensor_intarrayref_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern_nuclear_norm_tensor_intarrayref_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern_nuclear_norm_tensor_intarrayref_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nuclear_norm_out_tensor_tensor_intarrayref_bool)(void* out, void* self, void* dim, void* keepdim);
  HOST_API void* lantern_nuclear_norm_out_tensor_tensor_intarrayref_bool(void* out, void* self, void* dim, void* keepdim) { void* ret = _lantern_nuclear_norm_out_tensor_tensor_intarrayref_bool(out, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_clone_tensor_memoryformat)(void* self, void* memory_format);
  HOST_API void* lantern_clone_tensor_memoryformat(void* self, void* memory_format) { void* ret = _lantern_clone_tensor_memoryformat(self, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_clone_tensor_memoryformat)(void* self, void* memory_format);
  HOST_API void* lantern_Tensor_clone_tensor_memoryformat(void* self, void* memory_format) { void* ret = _lantern_Tensor_clone_tensor_memoryformat(self, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_resize_as__tensor_tensor_memoryformat)(void* self, void* the_template, void* memory_format);
  HOST_API void* lantern_resize_as__tensor_tensor_memoryformat(void* self, void* the_template, void* memory_format) { void* ret = _lantern_resize_as__tensor_tensor_memoryformat(self, the_template, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_resize_as__tensor_tensor_memoryformat)(void* self, void* the_template, void* memory_format);
  HOST_API void* lantern_Tensor_resize_as__tensor_tensor_memoryformat(void* self, void* the_template, void* memory_format) { void* ret = _lantern_Tensor_resize_as__tensor_tensor_memoryformat(self, the_template, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_out_tensor_tensor_scalar)(void* out, void* self, void* exponent);
  HOST_API void* lantern_pow_out_tensor_tensor_scalar(void* out, void* self, void* exponent) { void* ret = _lantern_pow_out_tensor_tensor_scalar(out, self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_tensor_scalar)(void* self, void* exponent);
  HOST_API void* lantern_pow_tensor_scalar(void* self, void* exponent) { void* ret = _lantern_pow_tensor_scalar(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pow_tensor_scalar)(void* self, void* exponent);
  HOST_API void* lantern_Tensor_pow_tensor_scalar(void* self, void* exponent) { void* ret = _lantern_Tensor_pow_tensor_scalar(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_zero__tensor)(void* self);
  HOST_API void* lantern_zero__tensor(void* self) { void* ret = _lantern_zero__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_zero__tensor)(void* self);
  HOST_API void* lantern_Tensor_zero__tensor(void* self) { void* ret = _lantern_Tensor_zero__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sub_out_tensor_tensor_tensor_scalar)(void* out, void* self, void* other, void* alpha);
  HOST_API void* lantern_sub_out_tensor_tensor_tensor_scalar(void* out, void* self, void* other, void* alpha) { void* ret = _lantern_sub_out_tensor_tensor_tensor_scalar(out, self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sub_tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_sub_tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_sub_tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sub_tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_sub_tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_sub_tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sub__tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_sub__tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_sub__tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sub_tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_sub_tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_sub_tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sub_tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_sub_tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_sub_tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sub__tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_Tensor_sub__tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_Tensor_sub__tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rsub_tensor_tensor_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_rsub_tensor_tensor_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_rsub_tensor_tensor_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rsub_tensor_scalar_scalar)(void* self, void* other, void* alpha);
  HOST_API void* lantern_rsub_tensor_scalar_scalar(void* self, void* other, void* alpha) { void* ret = _lantern_rsub_tensor_scalar_scalar(self, other, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_addmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* sparse, void* dense, void* beta, void* alpha);
  HOST_API void* lantern__sparse_addmm_tensor_tensor_tensor_scalar_scalar(void* self, void* sparse, void* dense, void* beta, void* alpha) { void* ret = _lantern__sparse_addmm_tensor_tensor_tensor_scalar_scalar(self, sparse, dense, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addmm_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_addmm_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_addmm_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_addmm_tensor_tensor_tensor_scalar_scalar(void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_addmm_tensor_tensor_tensor_scalar_scalar(self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addmm_tensor_tensor_tensor_scalar_scalar(void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addmm_tensor_tensor_tensor_scalar_scalar(self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addmm__tensor_tensor_tensor_scalar_scalar)(void* self, void* mat1, void* mat2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addmm__tensor_tensor_tensor_scalar_scalar(void* self, void* mat1, void* mat2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addmm__tensor_tensor_tensor_scalar_scalar(self, mat1, mat2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sparse_coo_tensor_intarrayref_tensoroptions)(void* size, void* options);
  HOST_API void* lantern_sparse_coo_tensor_intarrayref_tensoroptions(void* size, void* options) { void* ret = _lantern_sparse_coo_tensor_intarrayref_tensoroptions(size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sparse_coo_tensor_tensor_tensor_tensoroptions)(void* indices, void* values, void* options);
  HOST_API void* lantern_sparse_coo_tensor_tensor_tensor_tensoroptions(void* indices, void* values, void* options) { void* ret = _lantern_sparse_coo_tensor_tensor_tensor_tensoroptions(indices, values, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sparse_coo_tensor_tensor_tensor_intarrayref_tensoroptions)(void* indices, void* values, void* size, void* options);
  HOST_API void* lantern_sparse_coo_tensor_tensor_tensor_intarrayref_tensoroptions(void* indices, void* values, void* size, void* options) { void* ret = _lantern_sparse_coo_tensor_tensor_tensor_intarrayref_tensoroptions(indices, values, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_coo_tensor_unsafe_tensor_tensor_intarrayref_tensoroptions)(void* indices, void* values, void* size, void* options);
  HOST_API void* lantern__sparse_coo_tensor_unsafe_tensor_tensor_intarrayref_tensoroptions(void* indices, void* values, void* size, void* options) { void* ret = _lantern__sparse_coo_tensor_unsafe_tensor_tensor_intarrayref_tensoroptions(indices, values, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_coo_tensor_with_dims_intt_intt_intarrayref_tensoroptions)(void* sparse_dim, void* dense_dim, void* size, void* options);
  HOST_API void* lantern__sparse_coo_tensor_with_dims_intt_intt_intarrayref_tensoroptions(void* sparse_dim, void* dense_dim, void* size, void* options) { void* ret = _lantern__sparse_coo_tensor_with_dims_intt_intt_intarrayref_tensoroptions(sparse_dim, dense_dim, size, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__sparse_coo_tensor_with_dims_and_tensors_intt_intt_intarrayref_tensor_tensor_tensoroptions)(void* sparse_dim, void* dense_dim, void* size, void* indices, void* values, void* options);
  HOST_API void* lantern__sparse_coo_tensor_with_dims_and_tensors_intt_intt_intarrayref_tensor_tensor_tensoroptions(void* sparse_dim, void* dense_dim, void* size, void* indices, void* values, void* options) { void* ret = _lantern__sparse_coo_tensor_with_dims_and_tensors_intt_intt_intarrayref_tensor_tensor_tensoroptions(sparse_dim, dense_dim, size, indices, values, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sparse_resize__tensor_intarrayref_intt_intt)(void* self, void* size, void* sparse_dim, void* dense_dim);
  HOST_API void* lantern_Tensor_sparse_resize__tensor_intarrayref_intt_intt(void* self, void* size, void* sparse_dim, void* dense_dim) { void* ret = _lantern_Tensor_sparse_resize__tensor_intarrayref_intt_intt(self, size, sparse_dim, dense_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sparse_resize_and_clear__tensor_intarrayref_intt_intt)(void* self, void* size, void* sparse_dim, void* dense_dim);
  HOST_API void* lantern_Tensor_sparse_resize_and_clear__tensor_intarrayref_intt_intt(void* self, void* size, void* sparse_dim, void* dense_dim) { void* ret = _lantern_Tensor_sparse_resize_and_clear__tensor_intarrayref_intt_intt(self, size, sparse_dim, dense_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sparse_mask_tensor_tensor)(void* self, void* mask);
  HOST_API void* lantern_Tensor_sparse_mask_tensor_tensor(void* self, void* mask) { void* ret = _lantern_Tensor_sparse_mask_tensor_tensor(self, mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_dense_tensor)(void* self);
  HOST_API void* lantern_Tensor_to_dense_tensor(void* self) { void* ret = _lantern_Tensor_to_dense_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_to_dense_backward_tensor_tensor)(void* grad, void* input);
  HOST_API void* lantern_to_dense_backward_tensor_tensor(void* grad, void* input) { void* ret = _lantern_to_dense_backward_tensor_tensor(grad, input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sparse_dim_tensor)(void* self);
  HOST_API void* lantern_Tensor_sparse_dim_tensor(void* self) { void* ret = _lantern_Tensor_sparse_dim_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__dimi_tensor)(void* self);
  HOST_API void* lantern_Tensor__dimi_tensor(void* self) { void* ret = _lantern_Tensor__dimi_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_dense_dim_tensor)(void* self);
  HOST_API void* lantern_Tensor_dense_dim_tensor(void* self) { void* ret = _lantern_Tensor_dense_dim_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__dimv_tensor)(void* self);
  HOST_API void* lantern_Tensor__dimv_tensor(void* self) { void* ret = _lantern_Tensor__dimv_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__nnz_tensor)(void* self);
  HOST_API void* lantern_Tensor__nnz_tensor(void* self) { void* ret = _lantern_Tensor__nnz_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_coalesce_tensor)(void* self);
  HOST_API void* lantern_Tensor_coalesce_tensor(void* self) { void* ret = _lantern_Tensor_coalesce_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_coalesced_tensor)(void* self);
  HOST_API void* lantern_Tensor_is_coalesced_tensor(void* self) { void* ret = _lantern_Tensor_is_coalesced_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__indices_tensor)(void* self);
  HOST_API void* lantern_Tensor__indices_tensor(void* self) { void* ret = _lantern_Tensor__indices_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__values_tensor)(void* self);
  HOST_API void* lantern_Tensor__values_tensor(void* self) { void* ret = _lantern_Tensor__values_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor__coalesced__tensor_bool)(void* self, void* coalesced);
  HOST_API void* lantern_Tensor__coalesced__tensor_bool(void* self, void* coalesced) { void* ret = _lantern_Tensor__coalesced__tensor_bool(self, coalesced); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_indices_tensor)(void* self);
  HOST_API void* lantern_Tensor_indices_tensor(void* self) { void* ret = _lantern_Tensor_indices_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_values_tensor)(void* self);
  HOST_API void* lantern_Tensor_values_tensor(void* self) { void* ret = _lantern_Tensor_values_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hspmm_out_tensor_tensor_tensor)(void* out, void* mat1, void* mat2);
  HOST_API void* lantern_hspmm_out_tensor_tensor_tensor(void* out, void* mat1, void* mat2) { void* ret = _lantern_hspmm_out_tensor_tensor_tensor(out, mat1, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hspmm_tensor_tensor)(void* mat1, void* mat2);
  HOST_API void* lantern_hspmm_tensor_tensor(void* mat1, void* mat2) { void* ret = _lantern_hspmm_tensor_tensor(mat1, mat2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_copy_sparse_to_sparse__tensor_tensor_bool)(void* self, void* src, void* non_blocking);
  HOST_API void* lantern_copy_sparse_to_sparse__tensor_tensor_bool(void* self, void* src, void* non_blocking) { void* ret = _lantern_copy_sparse_to_sparse__tensor_tensor_bool(self, src, non_blocking); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unbind_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_unbind_tensor_intt(void* self, void* dim) { void* ret = _lantern_unbind_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unbind_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_Tensor_unbind_tensor_intt(void* self, void* dim) { void* ret = _lantern_Tensor_unbind_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_unbind_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_unbind_tensor_dimname(void* self, void* dim) { void* ret = _lantern_unbind_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unbind_tensor_dimname)(void* self, void* dim);
  HOST_API void* lantern_Tensor_unbind_tensor_dimname(void* self, void* dim) { void* ret = _lantern_Tensor_unbind_tensor_dimname(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_sparse_tensor_intt)(void* self, void* sparse_dim);
  HOST_API void* lantern_Tensor_to_sparse_tensor_intt(void* self, void* sparse_dim) { void* ret = _lantern_Tensor_to_sparse_tensor_intt(self, sparse_dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_sparse_tensor)(void* self);
  HOST_API void* lantern_Tensor_to_sparse_tensor(void* self) { void* ret = _lantern_Tensor_to_sparse_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_mkldnn_tensor)(void* self);
  HOST_API void* lantern_Tensor_to_mkldnn_tensor(void* self) { void* ret = _lantern_Tensor_to_mkldnn_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_reorder_conv2d_weight_tensor_intarrayref_intarrayref_intarrayref_intt)(void* self, void* padding, void* stride, void* dilation, void* groups);
  HOST_API void* lantern_mkldnn_reorder_conv2d_weight_tensor_intarrayref_intarrayref_intarrayref_intt(void* self, void* padding, void* stride, void* dilation, void* groups) { void* ret = _lantern_mkldnn_reorder_conv2d_weight_tensor_intarrayref_intarrayref_intarrayref_intt(self, padding, stride, dilation, groups); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_to_mkldnn_backward_tensor_tensor)(void* grad, void* input);
  HOST_API void* lantern_to_mkldnn_backward_tensor_tensor(void* grad, void* input) { void* ret = _lantern_to_mkldnn_backward_tensor_tensor(grad, input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantize_per_tensor_tensor_double_intt_scalartype)(void* self, void* scale, void* zero_point, void* dtype);
  HOST_API void* lantern_quantize_per_tensor_tensor_double_intt_scalartype(void* self, void* scale, void* zero_point, void* dtype) { void* ret = _lantern_quantize_per_tensor_tensor_double_intt_scalartype(self, scale, zero_point, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantize_per_channel_tensor_tensor_tensor_intt_scalartype)(void* self, void* scales, void* zero_points, void* axis, void* dtype);
  HOST_API void* lantern_quantize_per_channel_tensor_tensor_tensor_intt_scalartype(void* self, void* scales, void* zero_points, void* axis, void* dtype) { void* ret = _lantern_quantize_per_channel_tensor_tensor_tensor_intt_scalartype(self, scales, zero_points, axis, dtype); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dequantize_tensor)(void* self);
  HOST_API void* lantern_dequantize_tensor(void* self) { void* ret = _lantern_dequantize_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_dequantize_tensor)(void* self);
  HOST_API void* lantern_Tensor_dequantize_tensor(void* self) { void* ret = _lantern_Tensor_dequantize_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_q_scale_tensor)(void* self);
  HOST_API void* lantern_q_scale_tensor(void* self) { void* ret = _lantern_q_scale_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_q_scale_tensor)(void* self);
  HOST_API void* lantern_Tensor_q_scale_tensor(void* self) { void* ret = _lantern_Tensor_q_scale_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_q_zero_point_tensor)(void* self);
  HOST_API void* lantern_q_zero_point_tensor(void* self) { void* ret = _lantern_q_zero_point_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_q_zero_point_tensor)(void* self);
  HOST_API void* lantern_Tensor_q_zero_point_tensor(void* self) { void* ret = _lantern_Tensor_q_zero_point_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_q_per_channel_scales_tensor)(void* self);
  HOST_API void* lantern_q_per_channel_scales_tensor(void* self) { void* ret = _lantern_q_per_channel_scales_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_q_per_channel_scales_tensor)(void* self);
  HOST_API void* lantern_Tensor_q_per_channel_scales_tensor(void* self) { void* ret = _lantern_Tensor_q_per_channel_scales_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_q_per_channel_zero_points_tensor)(void* self);
  HOST_API void* lantern_q_per_channel_zero_points_tensor(void* self) { void* ret = _lantern_q_per_channel_zero_points_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_q_per_channel_zero_points_tensor)(void* self);
  HOST_API void* lantern_Tensor_q_per_channel_zero_points_tensor(void* self) { void* ret = _lantern_Tensor_q_per_channel_zero_points_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_q_per_channel_axis_tensor)(void* self);
  HOST_API void* lantern_q_per_channel_axis_tensor(void* self) { void* ret = _lantern_q_per_channel_axis_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_q_per_channel_axis_tensor)(void* self);
  HOST_API void* lantern_Tensor_q_per_channel_axis_tensor(void* self) { void* ret = _lantern_Tensor_q_per_channel_axis_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_int_repr_tensor)(void* self);
  HOST_API void* lantern_int_repr_tensor(void* self) { void* ret = _lantern_int_repr_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_int_repr_tensor)(void* self);
  HOST_API void* lantern_Tensor_int_repr_tensor(void* self) { void* ret = _lantern_Tensor_int_repr_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__make_per_tensor_quantized_tensor_tensor_double_intt)(void* self, void* scale, void* zero_point);
  HOST_API void* lantern__make_per_tensor_quantized_tensor_tensor_double_intt(void* self, void* scale, void* zero_point) { void* ret = _lantern__make_per_tensor_quantized_tensor_tensor_double_intt(self, scale, zero_point); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__make_per_channel_quantized_tensor_tensor_tensor_tensor_intt)(void* self, void* scale, void* zero_point, void* axis);
  HOST_API void* lantern__make_per_channel_quantized_tensor_tensor_tensor_tensor_intt(void* self, void* scale, void* zero_point, void* axis) { void* ret = _lantern__make_per_channel_quantized_tensor_tensor_tensor_tensor_intt(self, scale, zero_point, axis); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_qscheme_tensor)(void* self);
  HOST_API void* lantern_Tensor_qscheme_tensor(void* self) { void* ret = _lantern_Tensor_qscheme_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fake_quantize_per_tensor_affine_tensor_double_intt_intt_intt)(void* self, void* scale, void* zero_point, void* quant_min, void* quant_max);
  HOST_API void* lantern_fake_quantize_per_tensor_affine_tensor_double_intt_intt_intt(void* self, void* scale, void* zero_point, void* quant_min, void* quant_max) { void* ret = _lantern_fake_quantize_per_tensor_affine_tensor_double_intt_intt_intt(self, scale, zero_point, quant_min, quant_max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fake_quantize_per_tensor_affine_backward_tensor_tensor_double_intt_intt_intt)(void* grad, void* self, void* scale, void* zero_point, void* quant_min, void* quant_max);
  HOST_API void* lantern_fake_quantize_per_tensor_affine_backward_tensor_tensor_double_intt_intt_intt(void* grad, void* self, void* scale, void* zero_point, void* quant_min, void* quant_max) { void* ret = _lantern_fake_quantize_per_tensor_affine_backward_tensor_tensor_double_intt_intt_intt(grad, self, scale, zero_point, quant_min, quant_max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fake_quantize_per_channel_affine_tensor_tensor_tensor_intt_intt_intt)(void* self, void* scale, void* zero_point, void* axis, void* quant_min, void* quant_max);
  HOST_API void* lantern_fake_quantize_per_channel_affine_tensor_tensor_tensor_intt_intt_intt(void* self, void* scale, void* zero_point, void* axis, void* quant_min, void* quant_max) { void* ret = _lantern_fake_quantize_per_channel_affine_tensor_tensor_tensor_intt_intt_intt(self, scale, zero_point, axis, quant_min, quant_max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fake_quantize_per_channel_affine_backward_tensor_tensor_tensor_tensor_intt_intt_intt)(void* grad, void* self, void* scale, void* zero_point, void* axis, void* quant_min, void* quant_max);
  HOST_API void* lantern_fake_quantize_per_channel_affine_backward_tensor_tensor_tensor_tensor_intt_intt_intt(void* grad, void* self, void* scale, void* zero_point, void* axis, void* quant_min, void* quant_max) { void* ret = _lantern_fake_quantize_per_channel_affine_backward_tensor_tensor_tensor_tensor_intt_intt_intt(grad, self, scale, zero_point, axis, quant_min, quant_max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_tensor_tensoroptions_bool_bool_memoryformat)(void* self, void* options, void* non_blocking, void* copy, void* memory_format);
  HOST_API void* lantern_Tensor_to_tensor_tensoroptions_bool_bool_memoryformat(void* self, void* options, void* non_blocking, void* copy, void* memory_format) { void* ret = _lantern_Tensor_to_tensor_tensoroptions_bool_bool_memoryformat(self, options, non_blocking, copy, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_tensor_device_scalartype_bool_bool_memoryformat)(void* self, void* device, void* dtype, void* non_blocking, void* copy, void* memory_format);
  HOST_API void* lantern_Tensor_to_tensor_device_scalartype_bool_bool_memoryformat(void* self, void* device, void* dtype, void* non_blocking, void* copy, void* memory_format) { void* ret = _lantern_Tensor_to_tensor_device_scalartype_bool_bool_memoryformat(self, device, dtype, non_blocking, copy, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_tensor_scalartype_bool_bool_memoryformat)(void* self, void* dtype, void* non_blocking, void* copy, void* memory_format);
  HOST_API void* lantern_Tensor_to_tensor_scalartype_bool_bool_memoryformat(void* self, void* dtype, void* non_blocking, void* copy, void* memory_format) { void* ret = _lantern_Tensor_to_tensor_scalartype_bool_bool_memoryformat(self, dtype, non_blocking, copy, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_to_tensor_tensor_bool_bool_memoryformat)(void* self, void* other, void* non_blocking, void* copy, void* memory_format);
  HOST_API void* lantern_Tensor_to_tensor_tensor_bool_bool_memoryformat(void* self, void* other, void* non_blocking, void* copy, void* memory_format) { void* ret = _lantern_Tensor_to_tensor_tensor_bool_bool_memoryformat(self, other, non_blocking, copy, memory_format); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_meshgrid_tensorlist)(void* tensors);
  HOST_API void* lantern_meshgrid_tensorlist(void* tensors) { void* ret = _lantern_meshgrid_tensorlist(tensors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cartesian_prod_tensorlist)(void* tensors);
  HOST_API void* lantern_cartesian_prod_tensorlist(void* tensors) { void* ret = _lantern_cartesian_prod_tensorlist(tensors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_combinations_tensor_intt_bool)(void* self, void* r, void* with_replacement);
  HOST_API void* lantern_combinations_tensor_intt_bool(void* self, void* r, void* with_replacement) { void* ret = _lantern_combinations_tensor_intt_bool(self, r, with_replacement); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_item_tensor)(void* self);
  HOST_API void* lantern_Tensor_item_tensor(void* self) { void* ret = _lantern_Tensor_item_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_result_type_tensor_tensor)(void* tensor, void* other);
  HOST_API void* lantern_result_type_tensor_tensor(void* tensor, void* other) { void* ret = _lantern_result_type_tensor_tensor(tensor, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_result_type_tensor_scalar)(void* tensor, void* other);
  HOST_API void* lantern_result_type_tensor_scalar(void* tensor, void* other) { void* ret = _lantern_result_type_tensor_scalar(tensor, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_result_type_scalar_tensor)(void* scalar, void* tensor);
  HOST_API void* lantern_result_type_scalar_tensor(void* scalar, void* tensor) { void* ret = _lantern_result_type_scalar_tensor(scalar, tensor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_result_type_scalar_scalar)(void* scalar1, void* scalar2);
  HOST_API void* lantern_result_type_scalar_scalar(void* scalar1, void* scalar2) { void* ret = _lantern_result_type_scalar_scalar(scalar1, scalar2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_can_cast_scalartype_scalartype)(void* from, void* to);
  HOST_API void* lantern_can_cast_scalartype_scalartype(void* from, void* to) { void* ret = _lantern_can_cast_scalartype_scalartype(from, to); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_promote_types_scalartype_scalartype)(void* type1, void* type2);
  HOST_API void* lantern_promote_types_scalartype_scalartype(void* type1, void* type2) { void* ret = _lantern_promote_types_scalartype_scalartype(type1, type2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__local_scalar_dense_tensor)(void* self);
  HOST_API void* lantern__local_scalar_dense_tensor(void* self) { void* ret = _lantern__local_scalar_dense_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_fused_lstm_cell_tensor_tensor_tensor_tensor_tensor)(void* input_gates, void* hidden_gates, void* cx, void* input_bias, void* hidden_bias);
  HOST_API void* lantern__thnn_fused_lstm_cell_tensor_tensor_tensor_tensor_tensor(void* input_gates, void* hidden_gates, void* cx, void* input_bias, void* hidden_bias) { void* ret = _lantern__thnn_fused_lstm_cell_tensor_tensor_tensor_tensor_tensor(input_gates, hidden_gates, cx, input_bias, hidden_bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_fused_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_bool)(void* grad_hy, void* grad_cy, void* cx, void* cy, void* workspace, void* has_bias);
  HOST_API void* lantern__thnn_fused_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_bool(void* grad_hy, void* grad_cy, void* cx, void* cy, void* workspace, void* has_bias) { void* ret = _lantern__thnn_fused_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_bool(grad_hy, grad_cy, cx, cy, workspace, has_bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_differentiable_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor)(void* grad_hy, void* grad_cy, void* input_gates, void* hidden_gates, void* input_bias, void* hidden_bias, void* cx, void* cy);
  HOST_API void* lantern__thnn_differentiable_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor(void* grad_hy, void* grad_cy, void* input_gates, void* hidden_gates, void* input_bias, void* hidden_bias, void* cx, void* cy) { void* ret = _lantern__thnn_differentiable_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor(grad_hy, grad_cy, input_gates, hidden_gates, input_bias, hidden_bias, cx, cy); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_fused_gru_cell_tensor_tensor_tensor_tensor_tensor)(void* input_gates, void* hidden_gates, void* hx, void* input_bias, void* hidden_bias);
  HOST_API void* lantern__thnn_fused_gru_cell_tensor_tensor_tensor_tensor_tensor(void* input_gates, void* hidden_gates, void* hx, void* input_bias, void* hidden_bias) { void* ret = _lantern__thnn_fused_gru_cell_tensor_tensor_tensor_tensor_tensor(input_gates, hidden_gates, hx, input_bias, hidden_bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_fused_gru_cell_backward_tensor_tensor_bool)(void* grad_hy, void* workspace, void* has_bias);
  HOST_API void* lantern__thnn_fused_gru_cell_backward_tensor_tensor_bool(void* grad_hy, void* workspace, void* has_bias) { void* ret = _lantern__thnn_fused_gru_cell_backward_tensor_tensor_bool(grad_hy, workspace, has_bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__thnn_differentiable_gru_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor)(void* grad_hy, void* input_gates, void* hidden_gates, void* hx, void* input_bias, void* hidden_bias);
  HOST_API void* lantern__thnn_differentiable_gru_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor(void* grad_hy, void* input_gates, void* hidden_gates, void* hx, void* input_bias, void* hidden_bias) { void* ret = _lantern__thnn_differentiable_gru_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor(grad_hy, input_gates, hidden_gates, hx, input_bias, hidden_bias); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first);
  HOST_API void* lantern_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first) { void* ret = _lantern_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional);
  HOST_API void* lantern_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional) { void* ret = _lantern_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first);
  HOST_API void* lantern_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first) { void* ret = _lantern_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional);
  HOST_API void* lantern_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional) { void* ret = _lantern_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_tanh_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first);
  HOST_API void* lantern_rnn_tanh_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first) { void* ret = _lantern_rnn_tanh_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_tanh_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional);
  HOST_API void* lantern_rnn_tanh_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional) { void* ret = _lantern_rnn_tanh_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_relu_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first);
  HOST_API void* lantern_rnn_relu_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first) { void* ret = _lantern_rnn_relu_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_relu_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional);
  HOST_API void* lantern_rnn_relu_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional) { void* ret = _lantern_rnn_relu_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh);
  HOST_API void* lantern_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh) { void* ret = _lantern_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor(input, hx, w_ih, w_hh, b_ih, b_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh);
  HOST_API void* lantern_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh) { void* ret = _lantern_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor(input, hx, w_ih, w_hh, b_ih, b_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh);
  HOST_API void* lantern_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh) { void* ret = _lantern_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor(input, hx, w_ih, w_hh, b_ih, b_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh);
  HOST_API void* lantern_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh) { void* ret = _lantern_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor(input, hx, w_ih, w_hh, b_ih, b_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool_scalartype_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first, void* dtype, void* use_dynamic);
  HOST_API void* lantern_quantized_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool_scalartype_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first, void* dtype, void* use_dynamic) { void* ret = _lantern_quantized_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool_scalartype_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first, dtype, use_dynamic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_scalartype_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* dtype, void* use_dynamic);
  HOST_API void* lantern_quantized_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_scalartype_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* dtype, void* use_dynamic) { void* ret = _lantern_quantized_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_scalartype_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional, dtype, use_dynamic); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first);
  HOST_API void* lantern_quantized_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(void* input, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional, void* batch_first) { void* ret = _lantern_quantized_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool(input, hx, params, has_biases, num_layers, dropout, train, bidirectional, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional);
  HOST_API void* lantern_quantized_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(void* data, void* batch_sizes, void* hx, void* params, void* has_biases, void* num_layers, void* dropout, void* train, void* bidirectional) { void* ret = _lantern_quantized_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool(data, batch_sizes, hx, params, has_biases, num_layers, dropout, train, bidirectional); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh);
  HOST_API void* lantern_quantized_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh) { void* ret = _lantern_quantized_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(input, hx, w_ih, w_hh, b_ih, b_hh, packed_ih, packed_hh, col_offsets_ih, col_offsets_hh, scale_ih, scale_hh, zero_point_ih, zero_point_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh);
  HOST_API void* lantern_quantized_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh) { void* ret = _lantern_quantized_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(input, hx, w_ih, w_hh, b_ih, b_hh, packed_ih, packed_hh, col_offsets_ih, col_offsets_hh, scale_ih, scale_hh, zero_point_ih, zero_point_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh);
  HOST_API void* lantern_quantized_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh) { void* ret = _lantern_quantized_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(input, hx, w_ih, w_hh, b_ih, b_hh, packed_ih, packed_hh, col_offsets_ih, col_offsets_hh, scale_ih, scale_hh, zero_point_ih, zero_point_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_quantized_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh);
  HOST_API void* lantern_quantized_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(void* input, void* hx, void* w_ih, void* w_hh, void* b_ih, void* b_hh, void* packed_ih, void* packed_hh, void* col_offsets_ih, void* col_offsets_hh, void* scale_ih, void* scale_hh, void* zero_point_ih, void* zero_point_hh) { void* ret = _lantern_quantized_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar(input, hx, w_ih, w_hh, b_ih, b_hh, packed_ih, packed_hh, col_offsets_ih, col_offsets_hh, scale_ih, scale_hh, zero_point_ih, zero_point_hh); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__pack_padded_sequence_tensor_tensor_bool)(void* input, void* lengths, void* batch_first);
  HOST_API void* lantern__pack_padded_sequence_tensor_tensor_bool(void* input, void* lengths, void* batch_first) { void* ret = _lantern__pack_padded_sequence_tensor_tensor_bool(input, lengths, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__pack_padded_sequence_backward_tensor_intarrayref_tensor_bool)(void* grad, void* input_size, void* batch_sizes, void* batch_first);
  HOST_API void* lantern__pack_padded_sequence_backward_tensor_intarrayref_tensor_bool(void* grad, void* input_size, void* batch_sizes, void* batch_first) { void* ret = _lantern__pack_padded_sequence_backward_tensor_intarrayref_tensor_bool(grad, input_size, batch_sizes, batch_first); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__pad_packed_sequence_tensor_tensor_bool_scalar_intt)(void* data, void* batch_sizes, void* batch_first, void* padding_value, void* total_length);
  HOST_API void* lantern__pad_packed_sequence_tensor_tensor_bool_scalar_intt(void* data, void* batch_sizes, void* batch_first, void* padding_value, void* total_length) { void* ret = _lantern__pad_packed_sequence_tensor_tensor_bool_scalar_intt(data, batch_sizes, batch_first, padding_value, total_length); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set__tensor_storage)(void* self, void* source);
  HOST_API void* lantern_Tensor_set__tensor_storage(void* self, void* source) { void* ret = _lantern_Tensor_set__tensor_storage(self, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set__tensor_storage_intt_intarrayref_intarrayref)(void* self, void* source, void* storage_offset, void* size, void* stride);
  HOST_API void* lantern_Tensor_set__tensor_storage_intt_intarrayref_intarrayref(void* self, void* source, void* storage_offset, void* size, void* stride) { void* ret = _lantern_Tensor_set__tensor_storage_intt_intarrayref_intarrayref(self, source, storage_offset, size, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set__tensor_tensor)(void* self, void* source);
  HOST_API void* lantern_Tensor_set__tensor_tensor(void* self, void* source) { void* ret = _lantern_Tensor_set__tensor_tensor(self, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set__tensor)(void* self);
  HOST_API void* lantern_Tensor_set__tensor(void* self) { void* ret = _lantern_Tensor_set__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_set_quantizer__tensor_constquantizerptr)(void* self, void* quantizer);
  HOST_API void* lantern_Tensor_set_quantizer__tensor_constquantizerptr(void* self, void* quantizer) { void* ret = _lantern_Tensor_set_quantizer__tensor_constquantizerptr(self, quantizer); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_is_set_to_tensor_tensor)(void* self, void* tensor);
  HOST_API void* lantern_Tensor_is_set_to_tensor_tensor(void* self, void* tensor) { void* ret = _lantern_Tensor_is_set_to_tensor_tensor(self, tensor); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_fill__tensor_tensor_scalar)(void* self, void* mask, void* value);
  HOST_API void* lantern_Tensor_masked_fill__tensor_tensor_scalar(void* self, void* mask, void* value) { void* ret = _lantern_Tensor_masked_fill__tensor_tensor_scalar(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_masked_fill_tensor_tensor_scalar)(void* self, void* mask, void* value);
  HOST_API void* lantern_masked_fill_tensor_tensor_scalar(void* self, void* mask, void* value) { void* ret = _lantern_masked_fill_tensor_tensor_scalar(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_fill_tensor_tensor_scalar)(void* self, void* mask, void* value);
  HOST_API void* lantern_Tensor_masked_fill_tensor_tensor_scalar(void* self, void* mask, void* value) { void* ret = _lantern_Tensor_masked_fill_tensor_tensor_scalar(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_fill__tensor_tensor_tensor)(void* self, void* mask, void* value);
  HOST_API void* lantern_Tensor_masked_fill__tensor_tensor_tensor(void* self, void* mask, void* value) { void* ret = _lantern_Tensor_masked_fill__tensor_tensor_tensor(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_masked_fill_tensor_tensor_tensor)(void* self, void* mask, void* value);
  HOST_API void* lantern_masked_fill_tensor_tensor_tensor(void* self, void* mask, void* value) { void* ret = _lantern_masked_fill_tensor_tensor_tensor(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_fill_tensor_tensor_tensor)(void* self, void* mask, void* value);
  HOST_API void* lantern_Tensor_masked_fill_tensor_tensor_tensor(void* self, void* mask, void* value) { void* ret = _lantern_Tensor_masked_fill_tensor_tensor_tensor(self, mask, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_scatter__tensor_tensor_tensor)(void* self, void* mask, void* source);
  HOST_API void* lantern_Tensor_masked_scatter__tensor_tensor_tensor(void* self, void* mask, void* source) { void* ret = _lantern_Tensor_masked_scatter__tensor_tensor_tensor(self, mask, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_masked_scatter_tensor_tensor_tensor)(void* self, void* mask, void* source);
  HOST_API void* lantern_masked_scatter_tensor_tensor_tensor(void* self, void* mask, void* source) { void* ret = _lantern_masked_scatter_tensor_tensor_tensor(self, mask, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_scatter_tensor_tensor_tensor)(void* self, void* mask, void* source);
  HOST_API void* lantern_Tensor_masked_scatter_tensor_tensor_tensor(void* self, void* mask, void* source) { void* ret = _lantern_Tensor_masked_scatter_tensor_tensor_tensor(self, mask, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_view_tensor_intarrayref)(void* self, void* size);
  HOST_API void* lantern_Tensor_view_tensor_intarrayref(void* self, void* size) { void* ret = _lantern_Tensor_view_tensor_intarrayref(self, size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_put__tensor_tensor_tensor_bool)(void* self, void* index, void* source, void* accumulate);
  HOST_API void* lantern_Tensor_put__tensor_tensor_tensor_bool(void* self, void* index, void* source, void* accumulate) { void* ret = _lantern_Tensor_put__tensor_tensor_tensor_bool(self, index, source, accumulate); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_add__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_add__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_add__tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_add_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_index_add_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_index_add_tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_add_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_add_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_add_tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_add_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_index_add_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_index_add_tensor_dimname_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_add_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern_Tensor_index_add_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern_Tensor_index_add_tensor_dimname_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill__tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill__tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill__tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_fill_tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_index_fill_tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_index_fill_tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill_tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill_tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill_tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill__tensor_intt_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_fill_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_index_fill_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_index_fill_tensor_intt_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill_tensor_intt_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill__tensor_dimname_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill__tensor_dimname_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill__tensor_dimname_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill__tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill__tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill__tensor_dimname_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_fill_tensor_dimname_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_index_fill_tensor_dimname_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_index_fill_tensor_dimname_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill_tensor_dimname_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill_tensor_dimname_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill_tensor_dimname_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_fill_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_index_fill_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_index_fill_tensor_dimname_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_fill_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_index_fill_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_index_fill_tensor_dimname_tensor_tensor(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter__tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_scatter_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_scatter_tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter_tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter__tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_scatter__tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_scatter__tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_scatter_tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_scatter_tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_tensor_intt_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_scatter_tensor_intt_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_scatter_tensor_intt_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_scatter_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_scatter_tensor_dimname_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter_tensor_dimname_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_tensor_dimname_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_scatter_tensor_dimname_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_scatter_tensor_dimname_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_tensor_dimname_tensor_scalar)(void* self, void* dim, void* index, void* value);
  HOST_API void* lantern_Tensor_scatter_tensor_dimname_tensor_scalar(void* self, void* dim, void* index, void* value) { void* ret = _lantern_Tensor_scatter_tensor_dimname_tensor_scalar(self, dim, index, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_add__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter_add__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter_add__tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_add_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_scatter_add_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_scatter_add_tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_add_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter_add_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter_add_tensor_intt_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_scatter_add_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_scatter_add_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_scatter_add_tensor_dimname_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_scatter_add_tensor_dimname_tensor_tensor)(void* self, void* dim, void* index, void* src);
  HOST_API void* lantern_Tensor_scatter_add_tensor_dimname_tensor_tensor(void* self, void* dim, void* index, void* src) { void* ret = _lantern_Tensor_scatter_add_tensor_dimname_tensor_tensor(self, dim, index, src); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lt__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_lt__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_lt__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lt__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_lt__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_lt__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gt__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_gt__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_gt__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gt__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_gt__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_gt__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_le__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_le__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_le__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_le__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_le__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_le__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ge__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_ge__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_ge__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ge__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_ge__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_ge__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_eq__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_eq__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_eq__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_eq__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_eq__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_eq__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ne__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_ne__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_ne__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ne__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_ne__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_ne__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_and_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_and_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_bitwise_and_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_and_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_and_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_bitwise_and_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_and_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_bitwise_and_tensor_scalar(void* self, void* other) { void* ret = _lantern_bitwise_and_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_and_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_and_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_and_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_and_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_bitwise_and_tensor_tensor(void* self, void* other) { void* ret = _lantern_bitwise_and_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_and_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_and_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_and_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_and__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_and__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_and__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_and__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_and__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_and__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___and___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern___and___tensor_scalar(void* self, void* other) { void* ret = _lantern___and___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___and___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___and___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___and___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___and___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern___and___tensor_tensor(void* self, void* other) { void* ret = _lantern___and___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___and___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___and___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___and___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___iand___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___iand___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___iand___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___iand___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___iand___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___iand___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_or_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_or_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_bitwise_or_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_or_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_or_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_bitwise_or_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_or_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_bitwise_or_tensor_scalar(void* self, void* other) { void* ret = _lantern_bitwise_or_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_or_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_or_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_or_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_or_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_bitwise_or_tensor_tensor(void* self, void* other) { void* ret = _lantern_bitwise_or_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_or_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_or_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_or_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_or__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_or__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_or__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_or__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_or__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_or__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___or___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern___or___tensor_scalar(void* self, void* other) { void* ret = _lantern___or___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___or___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___or___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___or___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___or___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern___or___tensor_tensor(void* self, void* other) { void* ret = _lantern___or___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___or___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___or___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___or___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ior___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___ior___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___ior___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ior___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___ior___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___ior___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_xor_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_xor_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_bitwise_xor_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_xor_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_bitwise_xor_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_bitwise_xor_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_xor_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_bitwise_xor_tensor_scalar(void* self, void* other) { void* ret = _lantern_bitwise_xor_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_xor_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_xor_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_xor_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_bitwise_xor_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_bitwise_xor_tensor_tensor(void* self, void* other) { void* ret = _lantern_bitwise_xor_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_xor_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_xor_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_xor_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_xor__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_xor__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_xor__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_bitwise_xor__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_bitwise_xor__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_bitwise_xor__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___xor___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern___xor___tensor_scalar(void* self, void* other) { void* ret = _lantern___xor___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___xor___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___xor___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___xor___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___xor___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern___xor___tensor_tensor(void* self, void* other) { void* ret = _lantern___xor___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___xor___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___xor___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___xor___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ixor___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___ixor___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___ixor___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ixor___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___ixor___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___ixor___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___lshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern___lshift___tensor_scalar(void* self, void* other) { void* ret = _lantern___lshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___lshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___lshift___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___lshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___lshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern___lshift___tensor_tensor(void* self, void* other) { void* ret = _lantern___lshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___lshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___lshift___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___lshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ilshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___ilshift___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___ilshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___ilshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___ilshift___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___ilshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___rshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern___rshift___tensor_scalar(void* self, void* other) { void* ret = _lantern___rshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___rshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___rshift___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___rshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern___rshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern___rshift___tensor_tensor(void* self, void* other) { void* ret = _lantern___rshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___rshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___rshift___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___rshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___irshift___tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor___irshift___tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor___irshift___tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor___irshift___tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor___irshift___tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor___irshift___tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lgamma__tensor)(void* self);
  HOST_API void* lantern_Tensor_lgamma__tensor(void* self) { void* ret = _lantern_Tensor_lgamma__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_atan2__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_atan2__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_atan2__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tril__tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_Tensor_tril__tensor_intt(void* self, void* diagonal) { void* ret = _lantern_Tensor_tril__tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_triu__tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_Tensor_triu__tensor_intt(void* self, void* diagonal) { void* ret = _lantern_Tensor_triu__tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_digamma__tensor)(void* self);
  HOST_API void* lantern_Tensor_digamma__tensor(void* self) { void* ret = _lantern_Tensor_digamma__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_polygamma__tensor_intt)(void* self, void* n);
  HOST_API void* lantern_Tensor_polygamma__tensor_intt(void* self, void* n) { void* ret = _lantern_Tensor_polygamma__tensor_intt(self, n); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_renorm__tensor_scalar_intt_scalar)(void* self, void* p, void* dim, void* maxnorm);
  HOST_API void* lantern_Tensor_renorm__tensor_scalar_intt_scalar(void* self, void* p, void* dim, void* maxnorm) { void* ret = _lantern_Tensor_renorm__tensor_scalar_intt_scalar(self, p, dim, maxnorm); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pow__tensor_scalar)(void* self, void* exponent);
  HOST_API void* lantern_Tensor_pow__tensor_scalar(void* self, void* exponent) { void* ret = _lantern_Tensor_pow__tensor_scalar(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pow__tensor_tensor)(void* self, void* exponent);
  HOST_API void* lantern_Tensor_pow__tensor_tensor(void* self, void* exponent) { void* ret = _lantern_Tensor_pow__tensor_tensor(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lerp__tensor_tensor_scalar)(void* self, void* end, void* weight);
  HOST_API void* lantern_Tensor_lerp__tensor_tensor_scalar(void* self, void* end, void* weight) { void* ret = _lantern_Tensor_lerp__tensor_tensor_scalar(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lerp__tensor_tensor_tensor)(void* self, void* end, void* weight);
  HOST_API void* lantern_Tensor_lerp__tensor_tensor_tensor(void* self, void* end, void* weight) { void* ret = _lantern_Tensor_lerp__tensor_tensor_tensor(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fmod__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_fmod__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_fmod__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fmod__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_fmod__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_fmod__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_remainder__tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_remainder__tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_remainder__tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_remainder__tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_remainder__tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_remainder__tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addbmm__tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addbmm__tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addbmm__tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addbmm_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_addbmm_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_addbmm_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addbmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_addbmm_tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_addbmm_tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addbmm_tensor_tensor_tensor_scalar_scalar)(void* self, void* batch1, void* batch2, void* beta, void* alpha);
  HOST_API void* lantern_Tensor_addbmm_tensor_tensor_tensor_scalar_scalar(void* self, void* batch1, void* batch2, void* beta, void* alpha) { void* ret = _lantern_Tensor_addbmm_tensor_tensor_tensor_scalar_scalar(self, batch1, batch2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addcdiv__tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_Tensor_addcdiv__tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_Tensor_addcdiv__tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_random__tensor_intt_intt_generator)(void* self, void* from, void* to, void* generator);
  HOST_API void* lantern_Tensor_random__tensor_intt_intt_generator(void* self, void* from, void* to, void* generator) { void* ret = _lantern_Tensor_random__tensor_intt_intt_generator(self, from, to, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_random__tensor_intt_generator)(void* self, void* to, void* generator);
  HOST_API void* lantern_Tensor_random__tensor_intt_generator(void* self, void* to, void* generator) { void* ret = _lantern_Tensor_random__tensor_intt_generator(self, to, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_random__tensor_generator)(void* self, void* generator);
  HOST_API void* lantern_Tensor_random__tensor_generator(void* self, void* generator) { void* ret = _lantern_Tensor_random__tensor_generator(self, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_uniform__tensor_double_double_generator)(void* self, void* from, void* to, void* generator);
  HOST_API void* lantern_Tensor_uniform__tensor_double_double_generator(void* self, void* from, void* to, void* generator) { void* ret = _lantern_Tensor_uniform__tensor_double_double_generator(self, from, to, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cauchy__tensor_double_double_generator)(void* self, void* median, void* sigma, void* generator);
  HOST_API void* lantern_Tensor_cauchy__tensor_double_double_generator(void* self, void* median, void* sigma, void* generator) { void* ret = _lantern_Tensor_cauchy__tensor_double_double_generator(self, median, sigma, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_log_normal__tensor_double_double_generator)(void* self, void* mean, void* std, void* generator);
  HOST_API void* lantern_Tensor_log_normal__tensor_double_double_generator(void* self, void* mean, void* std, void* generator) { void* ret = _lantern_Tensor_log_normal__tensor_double_double_generator(self, mean, std, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_exponential__tensor_double_generator)(void* self, void* lambd, void* generator);
  HOST_API void* lantern_Tensor_exponential__tensor_double_generator(void* self, void* lambd, void* generator) { void* ret = _lantern_Tensor_exponential__tensor_double_generator(self, lambd, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_geometric__tensor_double_generator)(void* self, void* p, void* generator);
  HOST_API void* lantern_Tensor_geometric__tensor_double_generator(void* self, void* p, void* generator) { void* ret = _lantern_Tensor_geometric__tensor_double_generator(self, p, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diag_out_tensor_tensor_intt)(void* out, void* self, void* diagonal);
  HOST_API void* lantern_diag_out_tensor_tensor_intt(void* out, void* self, void* diagonal) { void* ret = _lantern_diag_out_tensor_tensor_intt(out, self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_diag_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_diag_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_diag_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_diag_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_Tensor_diag_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_Tensor_diag_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cross_out_tensor_tensor_tensor_intt)(void* out, void* self, void* other, void* dim);
  HOST_API void* lantern_cross_out_tensor_tensor_tensor_intt(void* out, void* self, void* other, void* dim) { void* ret = _lantern_cross_out_tensor_tensor_tensor_intt(out, self, other, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cross_tensor_tensor_intt)(void* self, void* other, void* dim);
  HOST_API void* lantern_cross_tensor_tensor_intt(void* self, void* other, void* dim) { void* ret = _lantern_cross_tensor_tensor_intt(self, other, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cross_tensor_tensor_intt)(void* self, void* other, void* dim);
  HOST_API void* lantern_Tensor_cross_tensor_tensor_intt(void* self, void* other, void* dim) { void* ret = _lantern_Tensor_cross_tensor_tensor_intt(self, other, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triu_out_tensor_tensor_intt)(void* out, void* self, void* diagonal);
  HOST_API void* lantern_triu_out_tensor_tensor_intt(void* out, void* self, void* diagonal) { void* ret = _lantern_triu_out_tensor_tensor_intt(out, self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triu_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_triu_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_triu_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_triu_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_Tensor_triu_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_Tensor_triu_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tril_out_tensor_tensor_intt)(void* out, void* self, void* diagonal);
  HOST_API void* lantern_tril_out_tensor_tensor_intt(void* out, void* self, void* diagonal) { void* ret = _lantern_tril_out_tensor_tensor_intt(out, self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tril_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_tril_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_tril_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_tril_tensor_intt)(void* self, void* diagonal);
  HOST_API void* lantern_Tensor_tril_tensor_intt(void* self, void* diagonal) { void* ret = _lantern_Tensor_tril_tensor_intt(self, diagonal); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tril_indices_intt_intt_intt_tensoroptions)(void* row, void* col, void* offset, void* options);
  HOST_API void* lantern_tril_indices_intt_intt_intt_tensoroptions(void* row, void* col, void* offset, void* options) { void* ret = _lantern_tril_indices_intt_intt_intt_tensoroptions(row, col, offset, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triu_indices_intt_intt_intt_tensoroptions)(void* row, void* col, void* offset, void* options);
  HOST_API void* lantern_triu_indices_intt_intt_intt_tensoroptions(void* row, void* col, void* offset, void* options) { void* ret = _lantern_triu_indices_intt_intt_intt_tensoroptions(row, col, offset, options); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_trace_tensor)(void* self);
  HOST_API void* lantern_trace_tensor(void* self) { void* ret = _lantern_trace_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_trace_tensor)(void* self);
  HOST_API void* lantern_Tensor_trace_tensor(void* self) { void* ret = _lantern_Tensor_trace_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ne_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_ne_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_ne_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ne_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_ne_tensor_scalar(void* self, void* other) { void* ret = _lantern_ne_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ne_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_ne_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_ne_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ne_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_ne_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_ne_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ne_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_ne_tensor_tensor(void* self, void* other) { void* ret = _lantern_ne_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ne_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_ne_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_ne_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eq_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_eq_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_eq_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eq_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_eq_tensor_scalar(void* self, void* other) { void* ret = _lantern_eq_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_eq_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_eq_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_eq_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eq_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_eq_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_eq_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eq_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_eq_tensor_tensor(void* self, void* other) { void* ret = _lantern_eq_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_eq_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_eq_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_eq_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ge_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_ge_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_ge_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ge_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_ge_tensor_scalar(void* self, void* other) { void* ret = _lantern_ge_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ge_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_ge_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_ge_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ge_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_ge_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_ge_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ge_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_ge_tensor_tensor(void* self, void* other) { void* ret = _lantern_ge_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ge_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_ge_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_ge_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_le_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_le_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_le_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_le_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_le_tensor_scalar(void* self, void* other) { void* ret = _lantern_le_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_le_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_le_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_le_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_le_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_le_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_le_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_le_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_le_tensor_tensor(void* self, void* other) { void* ret = _lantern_le_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_le_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_le_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_le_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gt_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_gt_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_gt_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gt_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_gt_tensor_scalar(void* self, void* other) { void* ret = _lantern_gt_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gt_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_gt_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_gt_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gt_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_gt_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_gt_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gt_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_gt_tensor_tensor(void* self, void* other) { void* ret = _lantern_gt_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gt_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_gt_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_gt_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lt_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_lt_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_lt_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lt_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_lt_tensor_scalar(void* self, void* other) { void* ret = _lantern_lt_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lt_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_lt_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_lt_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lt_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_lt_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_lt_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lt_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_lt_tensor_tensor(void* self, void* other) { void* ret = _lantern_lt_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lt_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_lt_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_lt_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_take_out_tensor_tensor_tensor)(void* out, void* self, void* index);
  HOST_API void* lantern_take_out_tensor_tensor_tensor(void* out, void* self, void* index) { void* ret = _lantern_take_out_tensor_tensor_tensor(out, self, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_take_tensor_tensor)(void* self, void* index);
  HOST_API void* lantern_take_tensor_tensor(void* self, void* index) { void* ret = _lantern_take_tensor_tensor(self, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_take_tensor_tensor)(void* self, void* index);
  HOST_API void* lantern_Tensor_take_tensor_tensor(void* self, void* index) { void* ret = _lantern_Tensor_take_tensor_tensor(self, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_select_out_tensor_tensor_intt_tensor)(void* out, void* self, void* dim, void* index);
  HOST_API void* lantern_index_select_out_tensor_tensor_intt_tensor(void* out, void* self, void* dim, void* index) { void* ret = _lantern_index_select_out_tensor_tensor_intt_tensor(out, self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_select_tensor_intt_tensor)(void* self, void* dim, void* index);
  HOST_API void* lantern_index_select_tensor_intt_tensor(void* self, void* dim, void* index) { void* ret = _lantern_index_select_tensor_intt_tensor(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_select_tensor_intt_tensor)(void* self, void* dim, void* index);
  HOST_API void* lantern_Tensor_index_select_tensor_intt_tensor(void* self, void* dim, void* index) { void* ret = _lantern_Tensor_index_select_tensor_intt_tensor(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_select_out_tensor_tensor_dimname_tensor)(void* out, void* self, void* dim, void* index);
  HOST_API void* lantern_index_select_out_tensor_tensor_dimname_tensor(void* out, void* self, void* dim, void* index) { void* ret = _lantern_index_select_out_tensor_tensor_dimname_tensor(out, self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_index_select_tensor_dimname_tensor)(void* self, void* dim, void* index);
  HOST_API void* lantern_index_select_tensor_dimname_tensor(void* self, void* dim, void* index) { void* ret = _lantern_index_select_tensor_dimname_tensor(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_index_select_tensor_dimname_tensor)(void* self, void* dim, void* index);
  HOST_API void* lantern_Tensor_index_select_tensor_dimname_tensor(void* self, void* dim, void* index) { void* ret = _lantern_Tensor_index_select_tensor_dimname_tensor(self, dim, index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_masked_select_out_tensor_tensor_tensor)(void* out, void* self, void* mask);
  HOST_API void* lantern_masked_select_out_tensor_tensor_tensor(void* out, void* self, void* mask) { void* ret = _lantern_masked_select_out_tensor_tensor_tensor(out, self, mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_masked_select_tensor_tensor)(void* self, void* mask);
  HOST_API void* lantern_masked_select_tensor_tensor(void* self, void* mask) { void* ret = _lantern_masked_select_tensor_tensor(self, mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_masked_select_tensor_tensor)(void* self, void* mask);
  HOST_API void* lantern_Tensor_masked_select_tensor_tensor(void* self, void* mask) { void* ret = _lantern_Tensor_masked_select_tensor_tensor(self, mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nonzero_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_nonzero_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_nonzero_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nonzero_tensor)(void* self);
  HOST_API void* lantern_nonzero_tensor(void* self) { void* ret = _lantern_nonzero_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_nonzero_tensor)(void* self);
  HOST_API void* lantern_Tensor_nonzero_tensor(void* self) { void* ret = _lantern_Tensor_nonzero_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nonzero_numpy_tensor)(void* self);
  HOST_API void* lantern_nonzero_numpy_tensor(void* self) { void* ret = _lantern_nonzero_numpy_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_nonzero_numpy_tensor)(void* self);
  HOST_API void* lantern_Tensor_nonzero_numpy_tensor(void* self) { void* ret = _lantern_Tensor_nonzero_numpy_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gather_out_tensor_tensor_intt_tensor_bool)(void* out, void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_gather_out_tensor_tensor_intt_tensor_bool(void* out, void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_gather_out_tensor_tensor_intt_tensor_bool(out, self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gather_tensor_intt_tensor_bool)(void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_gather_tensor_intt_tensor_bool(void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_gather_tensor_intt_tensor_bool(self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gather_tensor_intt_tensor_bool)(void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_Tensor_gather_tensor_intt_tensor_bool(void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_Tensor_gather_tensor_intt_tensor_bool(self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gather_out_tensor_tensor_dimname_tensor_bool)(void* out, void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_gather_out_tensor_tensor_dimname_tensor_bool(void* out, void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_gather_out_tensor_tensor_dimname_tensor_bool(out, self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_gather_tensor_dimname_tensor_bool)(void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_gather_tensor_dimname_tensor_bool(void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_gather_tensor_dimname_tensor_bool(self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_gather_tensor_dimname_tensor_bool)(void* self, void* dim, void* index, void* sparse_grad);
  HOST_API void* lantern_Tensor_gather_tensor_dimname_tensor_bool(void* self, void* dim, void* index, void* sparse_grad) { void* ret = _lantern_Tensor_gather_tensor_dimname_tensor_bool(self, dim, index, sparse_grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__gather_sparse_backward_tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* grad);
  HOST_API void* lantern__gather_sparse_backward_tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* grad) { void* ret = _lantern__gather_sparse_backward_tensor_intt_tensor_tensor(self, dim, index, grad); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addcmul_out_tensor_tensor_tensor_tensor_scalar)(void* out, void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_addcmul_out_tensor_tensor_tensor_tensor_scalar(void* out, void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_addcmul_out_tensor_tensor_tensor_tensor_scalar(out, self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addcmul_tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_addcmul_tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_addcmul_tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addcmul_tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_Tensor_addcmul_tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_Tensor_addcmul_tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addcmul__tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_Tensor_addcmul__tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_Tensor_addcmul__tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addcdiv_out_tensor_tensor_tensor_tensor_scalar)(void* out, void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_addcdiv_out_tensor_tensor_tensor_tensor_scalar(void* out, void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_addcdiv_out_tensor_tensor_tensor_tensor_scalar(out, self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_addcdiv_tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_addcdiv_tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_addcdiv_tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_addcdiv_tensor_tensor_tensor_scalar)(void* self, void* tensor1, void* tensor2, void* value);
  HOST_API void* lantern_Tensor_addcdiv_tensor_tensor_tensor_scalar(void* self, void* tensor1, void* tensor2, void* value) { void* ret = _lantern_Tensor_addcdiv_tensor_tensor_tensor_scalar(self, tensor1, tensor2, value); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lstsq_out_tensor_tensor_tensor_tensor)(void* X, void* qr, void* self, void* A);
  HOST_API void* lantern_lstsq_out_tensor_tensor_tensor_tensor(void* X, void* qr, void* self, void* A) { void* ret = _lantern_lstsq_out_tensor_tensor_tensor_tensor(X, qr, self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lstsq_tensor_tensor)(void* self, void* A);
  HOST_API void* lantern_lstsq_tensor_tensor(void* self, void* A) { void* ret = _lantern_lstsq_tensor_tensor(self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lstsq_tensor_tensor)(void* self, void* A);
  HOST_API void* lantern_Tensor_lstsq_tensor_tensor(void* self, void* A) { void* ret = _lantern_Tensor_lstsq_tensor_tensor(self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triangular_solve_out_tensor_tensor_tensor_tensor_bool_bool_bool)(void* X, void* M, void* self, void* A, void* upper, void* transpose, void* unitriangular);
  HOST_API void* lantern_triangular_solve_out_tensor_tensor_tensor_tensor_bool_bool_bool(void* X, void* M, void* self, void* A, void* upper, void* transpose, void* unitriangular) { void* ret = _lantern_triangular_solve_out_tensor_tensor_tensor_tensor_bool_bool_bool(X, M, self, A, upper, transpose, unitriangular); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_triangular_solve_tensor_tensor_bool_bool_bool)(void* self, void* A, void* upper, void* transpose, void* unitriangular);
  HOST_API void* lantern_triangular_solve_tensor_tensor_bool_bool_bool(void* self, void* A, void* upper, void* transpose, void* unitriangular) { void* ret = _lantern_triangular_solve_tensor_tensor_bool_bool_bool(self, A, upper, transpose, unitriangular); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_triangular_solve_tensor_tensor_bool_bool_bool)(void* self, void* A, void* upper, void* transpose, void* unitriangular);
  HOST_API void* lantern_Tensor_triangular_solve_tensor_tensor_bool_bool_bool(void* self, void* A, void* upper, void* transpose, void* unitriangular) { void* ret = _lantern_Tensor_triangular_solve_tensor_tensor_bool_bool_bool(self, A, upper, transpose, unitriangular); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__triangular_solve_helper_tensor_tensor_bool_bool_bool)(void* self, void* A, void* upper, void* transpose, void* unitriangular);
  HOST_API void* lantern__triangular_solve_helper_tensor_tensor_bool_bool_bool(void* self, void* A, void* upper, void* transpose, void* unitriangular) { void* ret = _lantern__triangular_solve_helper_tensor_tensor_bool_bool_bool(self, A, upper, transpose, unitriangular); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_symeig_out_tensor_tensor_tensor_bool_bool)(void* e, void* V, void* self, void* eigenvectors, void* upper);
  HOST_API void* lantern_symeig_out_tensor_tensor_tensor_bool_bool(void* e, void* V, void* self, void* eigenvectors, void* upper) { void* ret = _lantern_symeig_out_tensor_tensor_tensor_bool_bool(e, V, self, eigenvectors, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_symeig_tensor_bool_bool)(void* self, void* eigenvectors, void* upper);
  HOST_API void* lantern_symeig_tensor_bool_bool(void* self, void* eigenvectors, void* upper) { void* ret = _lantern_symeig_tensor_bool_bool(self, eigenvectors, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_symeig_tensor_bool_bool)(void* self, void* eigenvectors, void* upper);
  HOST_API void* lantern_Tensor_symeig_tensor_bool_bool(void* self, void* eigenvectors, void* upper) { void* ret = _lantern_Tensor_symeig_tensor_bool_bool(self, eigenvectors, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__symeig_helper_tensor_bool_bool)(void* self, void* eigenvectors, void* upper);
  HOST_API void* lantern__symeig_helper_tensor_bool_bool(void* self, void* eigenvectors, void* upper) { void* ret = _lantern__symeig_helper_tensor_bool_bool(self, eigenvectors, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eig_out_tensor_tensor_tensor_bool)(void* e, void* v, void* self, void* eigenvectors);
  HOST_API void* lantern_eig_out_tensor_tensor_tensor_bool(void* e, void* v, void* self, void* eigenvectors) { void* ret = _lantern_eig_out_tensor_tensor_tensor_bool(e, v, self, eigenvectors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_eig_tensor_bool)(void* self, void* eigenvectors);
  HOST_API void* lantern_eig_tensor_bool(void* self, void* eigenvectors) { void* ret = _lantern_eig_tensor_bool(self, eigenvectors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_eig_tensor_bool)(void* self, void* eigenvectors);
  HOST_API void* lantern_Tensor_eig_tensor_bool(void* self, void* eigenvectors) { void* ret = _lantern_Tensor_eig_tensor_bool(self, eigenvectors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_svd_out_tensor_tensor_tensor_tensor_bool_bool)(void* U, void* S, void* V, void* self, void* some, void* compute_uv);
  HOST_API void* lantern_svd_out_tensor_tensor_tensor_tensor_bool_bool(void* U, void* S, void* V, void* self, void* some, void* compute_uv) { void* ret = _lantern_svd_out_tensor_tensor_tensor_tensor_bool_bool(U, S, V, self, some, compute_uv); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_svd_tensor_bool_bool)(void* self, void* some, void* compute_uv);
  HOST_API void* lantern_svd_tensor_bool_bool(void* self, void* some, void* compute_uv) { void* ret = _lantern_svd_tensor_bool_bool(self, some, compute_uv); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_svd_tensor_bool_bool)(void* self, void* some, void* compute_uv);
  HOST_API void* lantern_Tensor_svd_tensor_bool_bool(void* self, void* some, void* compute_uv) { void* ret = _lantern_Tensor_svd_tensor_bool_bool(self, some, compute_uv); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__svd_helper_tensor_bool_bool)(void* self, void* some, void* compute_uv);
  HOST_API void* lantern__svd_helper_tensor_bool_bool(void* self, void* some, void* compute_uv) { void* ret = _lantern__svd_helper_tensor_bool_bool(self, some, compute_uv); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_out_tensor_tensor_bool)(void* out, void* self, void* upper);
  HOST_API void* lantern_cholesky_out_tensor_tensor_bool(void* out, void* self, void* upper) { void* ret = _lantern_cholesky_out_tensor_tensor_bool(out, self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_tensor_bool)(void* self, void* upper);
  HOST_API void* lantern_cholesky_tensor_bool(void* self, void* upper) { void* ret = _lantern_cholesky_tensor_bool(self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cholesky_tensor_bool)(void* self, void* upper);
  HOST_API void* lantern_Tensor_cholesky_tensor_bool(void* self, void* upper) { void* ret = _lantern_Tensor_cholesky_tensor_bool(self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cholesky_helper_tensor_bool)(void* self, void* upper);
  HOST_API void* lantern__cholesky_helper_tensor_bool(void* self, void* upper) { void* ret = _lantern__cholesky_helper_tensor_bool(self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_solve_out_tensor_tensor_tensor_bool)(void* out, void* self, void* input2, void* upper);
  HOST_API void* lantern_cholesky_solve_out_tensor_tensor_tensor_bool(void* out, void* self, void* input2, void* upper) { void* ret = _lantern_cholesky_solve_out_tensor_tensor_tensor_bool(out, self, input2, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_solve_tensor_tensor_bool)(void* self, void* input2, void* upper);
  HOST_API void* lantern_cholesky_solve_tensor_tensor_bool(void* self, void* input2, void* upper) { void* ret = _lantern_cholesky_solve_tensor_tensor_bool(self, input2, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cholesky_solve_tensor_tensor_bool)(void* self, void* input2, void* upper);
  HOST_API void* lantern_Tensor_cholesky_solve_tensor_tensor_bool(void* self, void* input2, void* upper) { void* ret = _lantern_Tensor_cholesky_solve_tensor_tensor_bool(self, input2, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cholesky_solve_helper_tensor_tensor_bool)(void* self, void* A, void* upper);
  HOST_API void* lantern__cholesky_solve_helper_tensor_tensor_bool(void* self, void* A, void* upper) { void* ret = _lantern__cholesky_solve_helper_tensor_tensor_bool(self, A, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_solve_tensor_tensor)(void* self, void* A);
  HOST_API void* lantern_solve_tensor_tensor(void* self, void* A) { void* ret = _lantern_solve_tensor_tensor(self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_solve_tensor_tensor)(void* self, void* A);
  HOST_API void* lantern_Tensor_solve_tensor_tensor(void* self, void* A) { void* ret = _lantern_Tensor_solve_tensor_tensor(self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_solve_out_tensor_tensor_tensor_tensor)(void* solution, void* lu, void* self, void* A);
  HOST_API void* lantern_solve_out_tensor_tensor_tensor_tensor(void* solution, void* lu, void* self, void* A) { void* ret = _lantern_solve_out_tensor_tensor_tensor_tensor(solution, lu, self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__solve_helper_tensor_tensor)(void* self, void* A);
  HOST_API void* lantern__solve_helper_tensor_tensor(void* self, void* A) { void* ret = _lantern__solve_helper_tensor_tensor(self, A); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_inverse_out_tensor_tensor_bool)(void* out, void* self, void* upper);
  HOST_API void* lantern_cholesky_inverse_out_tensor_tensor_bool(void* out, void* self, void* upper) { void* ret = _lantern_cholesky_inverse_out_tensor_tensor_bool(out, self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_cholesky_inverse_tensor_bool)(void* self, void* upper);
  HOST_API void* lantern_cholesky_inverse_tensor_bool(void* self, void* upper) { void* ret = _lantern_cholesky_inverse_tensor_bool(self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_cholesky_inverse_tensor_bool)(void* self, void* upper);
  HOST_API void* lantern_Tensor_cholesky_inverse_tensor_bool(void* self, void* upper) { void* ret = _lantern_Tensor_cholesky_inverse_tensor_bool(self, upper); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_qr_out_tensor_tensor_tensor_bool)(void* Q, void* R, void* self, void* some);
  HOST_API void* lantern_qr_out_tensor_tensor_tensor_bool(void* Q, void* R, void* self, void* some) { void* ret = _lantern_qr_out_tensor_tensor_tensor_bool(Q, R, self, some); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_qr_tensor_bool)(void* self, void* some);
  HOST_API void* lantern_qr_tensor_bool(void* self, void* some) { void* ret = _lantern_qr_tensor_bool(self, some); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_qr_tensor_bool)(void* self, void* some);
  HOST_API void* lantern_Tensor_qr_tensor_bool(void* self, void* some) { void* ret = _lantern_Tensor_qr_tensor_bool(self, some); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__qr_helper_tensor_bool)(void* self, void* some);
  HOST_API void* lantern__qr_helper_tensor_bool(void* self, void* some) { void* ret = _lantern__qr_helper_tensor_bool(self, some); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_geqrf_out_tensor_tensor_tensor)(void* a, void* tau, void* self);
  HOST_API void* lantern_geqrf_out_tensor_tensor_tensor(void* a, void* tau, void* self) { void* ret = _lantern_geqrf_out_tensor_tensor_tensor(a, tau, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_geqrf_tensor)(void* self);
  HOST_API void* lantern_geqrf_tensor(void* self) { void* ret = _lantern_geqrf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_geqrf_tensor)(void* self);
  HOST_API void* lantern_Tensor_geqrf_tensor(void* self) { void* ret = _lantern_Tensor_geqrf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_orgqr_out_tensor_tensor_tensor)(void* out, void* self, void* input2);
  HOST_API void* lantern_orgqr_out_tensor_tensor_tensor(void* out, void* self, void* input2) { void* ret = _lantern_orgqr_out_tensor_tensor_tensor(out, self, input2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_orgqr_tensor_tensor)(void* self, void* input2);
  HOST_API void* lantern_orgqr_tensor_tensor(void* self, void* input2) { void* ret = _lantern_orgqr_tensor_tensor(self, input2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_orgqr_tensor_tensor)(void* self, void* input2);
  HOST_API void* lantern_Tensor_orgqr_tensor_tensor(void* self, void* input2) { void* ret = _lantern_Tensor_orgqr_tensor_tensor(self, input2); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ormqr_out_tensor_tensor_tensor_tensor_bool_bool)(void* out, void* self, void* input2, void* input3, void* left, void* transpose);
  HOST_API void* lantern_ormqr_out_tensor_tensor_tensor_tensor_bool_bool(void* out, void* self, void* input2, void* input3, void* left, void* transpose) { void* ret = _lantern_ormqr_out_tensor_tensor_tensor_tensor_bool_bool(out, self, input2, input3, left, transpose); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_ormqr_tensor_tensor_tensor_bool_bool)(void* self, void* input2, void* input3, void* left, void* transpose);
  HOST_API void* lantern_ormqr_tensor_tensor_tensor_bool_bool(void* self, void* input2, void* input3, void* left, void* transpose) { void* ret = _lantern_ormqr_tensor_tensor_tensor_bool_bool(self, input2, input3, left, transpose); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_ormqr_tensor_tensor_tensor_bool_bool)(void* self, void* input2, void* input3, void* left, void* transpose);
  HOST_API void* lantern_Tensor_ormqr_tensor_tensor_tensor_bool_bool(void* self, void* input2, void* input3, void* left, void* transpose) { void* ret = _lantern_Tensor_ormqr_tensor_tensor_tensor_bool_bool(self, input2, input3, left, transpose); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__lu_with_info_tensor_bool_bool)(void* self, void* pivot, void* check_errors);
  HOST_API void* lantern__lu_with_info_tensor_bool_bool(void* self, void* pivot, void* check_errors) { void* ret = _lantern__lu_with_info_tensor_bool_bool(self, pivot, check_errors); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lu_solve_out_tensor_tensor_tensor_tensor)(void* out, void* self, void* LU_data, void* LU_pivots);
  HOST_API void* lantern_lu_solve_out_tensor_tensor_tensor_tensor(void* out, void* self, void* LU_data, void* LU_pivots) { void* ret = _lantern_lu_solve_out_tensor_tensor_tensor_tensor(out, self, LU_data, LU_pivots); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lu_solve_tensor_tensor_tensor)(void* self, void* LU_data, void* LU_pivots);
  HOST_API void* lantern_lu_solve_tensor_tensor_tensor(void* self, void* LU_data, void* LU_pivots) { void* ret = _lantern_lu_solve_tensor_tensor_tensor(self, LU_data, LU_pivots); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lu_solve_tensor_tensor_tensor)(void* self, void* LU_data, void* LU_pivots);
  HOST_API void* lantern_Tensor_lu_solve_tensor_tensor_tensor(void* self, void* LU_data, void* LU_pivots) { void* ret = _lantern_Tensor_lu_solve_tensor_tensor_tensor(self, LU_data, LU_pivots); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__lu_solve_helper_tensor_tensor_tensor)(void* self, void* LU_data, void* LU_pivots);
  HOST_API void* lantern__lu_solve_helper_tensor_tensor_tensor(void* self, void* LU_data, void* LU_pivots) { void* ret = _lantern__lu_solve_helper_tensor_tensor_tensor(self, LU_data, LU_pivots); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multinomial_out_tensor_tensor_intt_bool_generator)(void* out, void* self, void* num_samples, void* replacement, void* generator);
  HOST_API void* lantern_multinomial_out_tensor_tensor_intt_bool_generator(void* out, void* self, void* num_samples, void* replacement, void* generator) { void* ret = _lantern_multinomial_out_tensor_tensor_intt_bool_generator(out, self, num_samples, replacement, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multinomial_tensor_intt_bool_generator)(void* self, void* num_samples, void* replacement, void* generator);
  HOST_API void* lantern_multinomial_tensor_intt_bool_generator(void* self, void* num_samples, void* replacement, void* generator) { void* ret = _lantern_multinomial_tensor_intt_bool_generator(self, num_samples, replacement, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_multinomial_tensor_intt_bool_generator)(void* self, void* num_samples, void* replacement, void* generator);
  HOST_API void* lantern_Tensor_multinomial_tensor_intt_bool_generator(void* self, void* num_samples, void* replacement, void* generator) { void* ret = _lantern_Tensor_multinomial_tensor_intt_bool_generator(self, num_samples, replacement, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__multinomial_alias_setup_tensor)(void* probs);
  HOST_API void* lantern__multinomial_alias_setup_tensor(void* probs) { void* ret = _lantern__multinomial_alias_setup_tensor(probs); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__multinomial_alias_draw_tensor_tensor_intt_generator)(void* J, void* q, void* num_samples, void* generator);
  HOST_API void* lantern__multinomial_alias_draw_tensor_tensor_intt_generator(void* J, void* q, void* num_samples, void* generator) { void* ret = _lantern__multinomial_alias_draw_tensor_tensor_intt_generator(J, q, num_samples, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lgamma_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_lgamma_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_lgamma_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lgamma_tensor)(void* self);
  HOST_API void* lantern_lgamma_tensor(void* self) { void* ret = _lantern_lgamma_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lgamma_tensor)(void* self);
  HOST_API void* lantern_Tensor_lgamma_tensor(void* self) { void* ret = _lantern_Tensor_lgamma_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_digamma_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_digamma_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_digamma_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_digamma_tensor)(void* self);
  HOST_API void* lantern_digamma_tensor(void* self) { void* ret = _lantern_digamma_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_digamma_tensor)(void* self);
  HOST_API void* lantern_Tensor_digamma_tensor(void* self) { void* ret = _lantern_Tensor_digamma_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_polygamma_out_tensor_intt_tensor)(void* out, void* n, void* self);
  HOST_API void* lantern_polygamma_out_tensor_intt_tensor(void* out, void* n, void* self) { void* ret = _lantern_polygamma_out_tensor_intt_tensor(out, n, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erfinv_tensor)(void* self);
  HOST_API void* lantern_erfinv_tensor(void* self) { void* ret = _lantern_erfinv_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erfinv_tensor)(void* self);
  HOST_API void* lantern_Tensor_erfinv_tensor(void* self) { void* ret = _lantern_Tensor_erfinv_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_erfinv__tensor)(void* self);
  HOST_API void* lantern_Tensor_erfinv__tensor(void* self) { void* ret = _lantern_Tensor_erfinv__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_erfinv_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_erfinv_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_erfinv_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sign_tensor)(void* self);
  HOST_API void* lantern_sign_tensor(void* self) { void* ret = _lantern_sign_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sign_tensor)(void* self);
  HOST_API void* lantern_Tensor_sign_tensor(void* self) { void* ret = _lantern_Tensor_sign_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sign__tensor)(void* self);
  HOST_API void* lantern_Tensor_sign__tensor(void* self) { void* ret = _lantern_Tensor_sign__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sign_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_sign_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_sign_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_dist_tensor_tensor_scalar)(void* self, void* other, void* p);
  HOST_API void* lantern_dist_tensor_tensor_scalar(void* self, void* other, void* p) { void* ret = _lantern_dist_tensor_tensor_scalar(self, other, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_dist_tensor_tensor_scalar)(void* self, void* other, void* p);
  HOST_API void* lantern_Tensor_dist_tensor_tensor_scalar(void* self, void* other, void* p) { void* ret = _lantern_Tensor_dist_tensor_tensor_scalar(self, other, p); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_atan2_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_atan2_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_atan2_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_atan2_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_atan2_tensor_tensor(void* self, void* other) { void* ret = _lantern_atan2_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_atan2_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_atan2_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_atan2_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lerp_out_tensor_tensor_tensor_scalar)(void* out, void* self, void* end, void* weight);
  HOST_API void* lantern_lerp_out_tensor_tensor_tensor_scalar(void* out, void* self, void* end, void* weight) { void* ret = _lantern_lerp_out_tensor_tensor_tensor_scalar(out, self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lerp_out_tensor_tensor_tensor_tensor)(void* out, void* self, void* end, void* weight);
  HOST_API void* lantern_lerp_out_tensor_tensor_tensor_tensor(void* out, void* self, void* end, void* weight) { void* ret = _lantern_lerp_out_tensor_tensor_tensor_tensor(out, self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lerp_tensor_tensor_scalar)(void* self, void* end, void* weight);
  HOST_API void* lantern_lerp_tensor_tensor_scalar(void* self, void* end, void* weight) { void* ret = _lantern_lerp_tensor_tensor_scalar(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lerp_tensor_tensor_scalar)(void* self, void* end, void* weight);
  HOST_API void* lantern_Tensor_lerp_tensor_tensor_scalar(void* self, void* end, void* weight) { void* ret = _lantern_Tensor_lerp_tensor_tensor_scalar(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_lerp_tensor_tensor_tensor)(void* self, void* end, void* weight);
  HOST_API void* lantern_lerp_tensor_tensor_tensor(void* self, void* end, void* weight) { void* ret = _lantern_lerp_tensor_tensor_tensor(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_lerp_tensor_tensor_tensor)(void* self, void* end, void* weight);
  HOST_API void* lantern_Tensor_lerp_tensor_tensor_tensor(void* self, void* end, void* weight) { void* ret = _lantern_Tensor_lerp_tensor_tensor_tensor(self, end, weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_histc_out_tensor_tensor_intt_scalar_scalar)(void* out, void* self, void* bins, void* min, void* max);
  HOST_API void* lantern_histc_out_tensor_tensor_intt_scalar_scalar(void* out, void* self, void* bins, void* min, void* max) { void* ret = _lantern_histc_out_tensor_tensor_intt_scalar_scalar(out, self, bins, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_histc_tensor_intt_scalar_scalar)(void* self, void* bins, void* min, void* max);
  HOST_API void* lantern_histc_tensor_intt_scalar_scalar(void* self, void* bins, void* min, void* max) { void* ret = _lantern_histc_tensor_intt_scalar_scalar(self, bins, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_histc_tensor_intt_scalar_scalar)(void* self, void* bins, void* min, void* max);
  HOST_API void* lantern_Tensor_histc_tensor_intt_scalar_scalar(void* self, void* bins, void* min, void* max) { void* ret = _lantern_Tensor_histc_tensor_intt_scalar_scalar(self, bins, min, max); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fmod_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_fmod_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_fmod_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fmod_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_fmod_tensor_scalar(void* self, void* other) { void* ret = _lantern_fmod_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fmod_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_fmod_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_fmod_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fmod_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_fmod_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_fmod_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fmod_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_fmod_tensor_tensor(void* self, void* other) { void* ret = _lantern_fmod_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_fmod_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_fmod_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_fmod_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_remainder_out_tensor_tensor_scalar)(void* out, void* self, void* other);
  HOST_API void* lantern_remainder_out_tensor_tensor_scalar(void* out, void* self, void* other) { void* ret = _lantern_remainder_out_tensor_tensor_scalar(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_remainder_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_remainder_tensor_scalar(void* self, void* other) { void* ret = _lantern_remainder_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_remainder_tensor_scalar)(void* self, void* other);
  HOST_API void* lantern_Tensor_remainder_tensor_scalar(void* self, void* other) { void* ret = _lantern_Tensor_remainder_tensor_scalar(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_remainder_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_remainder_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_remainder_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_remainder_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_remainder_tensor_tensor(void* self, void* other) { void* ret = _lantern_remainder_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_remainder_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_remainder_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_remainder_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_min_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_min_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_min_tensor_tensor(void* self, void* other) { void* ret = _lantern_min_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_min_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_min_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_min_tensor)(void* self);
  HOST_API void* lantern_min_tensor(void* self) { void* ret = _lantern_min_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_min_tensor)(void* self);
  HOST_API void* lantern_Tensor_min_tensor(void* self) { void* ret = _lantern_Tensor_min_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_out_tensor_tensor_tensor)(void* out, void* self, void* other);
  HOST_API void* lantern_max_out_tensor_tensor_tensor(void* out, void* self, void* other) { void* ret = _lantern_max_out_tensor_tensor_tensor(out, self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_max_tensor_tensor(void* self, void* other) { void* ret = _lantern_max_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_max_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_max_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_tensor)(void* self);
  HOST_API void* lantern_max_tensor(void* self) { void* ret = _lantern_max_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_max_tensor)(void* self);
  HOST_API void* lantern_Tensor_max_tensor(void* self) { void* ret = _lantern_Tensor_max_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_median_tensor)(void* self);
  HOST_API void* lantern_median_tensor(void* self) { void* ret = _lantern_median_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_median_tensor)(void* self);
  HOST_API void* lantern_Tensor_median_tensor(void* self) { void* ret = _lantern_Tensor_median_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sort_out_tensor_tensor_tensor_intt_bool)(void* values, void* indices, void* self, void* dim, void* descending);
  HOST_API void* lantern_sort_out_tensor_tensor_tensor_intt_bool(void* values, void* indices, void* self, void* dim, void* descending) { void* ret = _lantern_sort_out_tensor_tensor_tensor_intt_bool(values, indices, self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sort_tensor_intt_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_sort_tensor_intt_bool(void* self, void* dim, void* descending) { void* ret = _lantern_sort_tensor_intt_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sort_tensor_intt_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_Tensor_sort_tensor_intt_bool(void* self, void* dim, void* descending) { void* ret = _lantern_Tensor_sort_tensor_intt_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sort_out_tensor_tensor_tensor_dimname_bool)(void* values, void* indices, void* self, void* dim, void* descending);
  HOST_API void* lantern_sort_out_tensor_tensor_tensor_dimname_bool(void* values, void* indices, void* self, void* dim, void* descending) { void* ret = _lantern_sort_out_tensor_tensor_tensor_dimname_bool(values, indices, self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sort_tensor_dimname_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_sort_tensor_dimname_bool(void* self, void* dim, void* descending) { void* ret = _lantern_sort_tensor_dimname_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_sort_tensor_dimname_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_Tensor_sort_tensor_dimname_bool(void* self, void* dim, void* descending) { void* ret = _lantern_Tensor_sort_tensor_dimname_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_argsort_tensor_intt_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_argsort_tensor_intt_bool(void* self, void* dim, void* descending) { void* ret = _lantern_argsort_tensor_intt_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_argsort_tensor_intt_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_Tensor_argsort_tensor_intt_bool(void* self, void* dim, void* descending) { void* ret = _lantern_Tensor_argsort_tensor_intt_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_argsort_tensor_dimname_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_argsort_tensor_dimname_bool(void* self, void* dim, void* descending) { void* ret = _lantern_argsort_tensor_dimname_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_argsort_tensor_dimname_bool)(void* self, void* dim, void* descending);
  HOST_API void* lantern_Tensor_argsort_tensor_dimname_bool(void* self, void* dim, void* descending) { void* ret = _lantern_Tensor_argsort_tensor_dimname_bool(self, dim, descending); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_topk_out_tensor_tensor_tensor_intt_intt_bool_bool)(void* values, void* indices, void* self, void* k, void* dim, void* largest, void* sorted);
  HOST_API void* lantern_topk_out_tensor_tensor_tensor_intt_intt_bool_bool(void* values, void* indices, void* self, void* k, void* dim, void* largest, void* sorted) { void* ret = _lantern_topk_out_tensor_tensor_tensor_intt_intt_bool_bool(values, indices, self, k, dim, largest, sorted); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_topk_tensor_intt_intt_bool_bool)(void* self, void* k, void* dim, void* largest, void* sorted);
  HOST_API void* lantern_topk_tensor_intt_intt_bool_bool(void* self, void* k, void* dim, void* largest, void* sorted) { void* ret = _lantern_topk_tensor_intt_intt_bool_bool(self, k, dim, largest, sorted); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_topk_tensor_intt_intt_bool_bool)(void* self, void* k, void* dim, void* largest, void* sorted);
  HOST_API void* lantern_Tensor_topk_tensor_intt_intt_bool_bool(void* self, void* k, void* dim, void* largest, void* sorted) { void* ret = _lantern_Tensor_topk_tensor_intt_intt_bool_bool(self, k, dim, largest, sorted); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_all_tensor)(void* self);
  HOST_API void* lantern_all_tensor(void* self) { void* ret = _lantern_all_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_all_tensor)(void* self);
  HOST_API void* lantern_Tensor_all_tensor(void* self) { void* ret = _lantern_Tensor_all_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_any_tensor)(void* self);
  HOST_API void* lantern_any_tensor(void* self) { void* ret = _lantern_any_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_any_tensor)(void* self);
  HOST_API void* lantern_Tensor_any_tensor(void* self) { void* ret = _lantern_Tensor_any_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_renorm_out_tensor_tensor_scalar_intt_scalar)(void* out, void* self, void* p, void* dim, void* maxnorm);
  HOST_API void* lantern_renorm_out_tensor_tensor_scalar_intt_scalar(void* out, void* self, void* p, void* dim, void* maxnorm) { void* ret = _lantern_renorm_out_tensor_tensor_scalar_intt_scalar(out, self, p, dim, maxnorm); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_renorm_tensor_scalar_intt_scalar)(void* self, void* p, void* dim, void* maxnorm);
  HOST_API void* lantern_renorm_tensor_scalar_intt_scalar(void* self, void* p, void* dim, void* maxnorm) { void* ret = _lantern_renorm_tensor_scalar_intt_scalar(self, p, dim, maxnorm); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_renorm_tensor_scalar_intt_scalar)(void* self, void* p, void* dim, void* maxnorm);
  HOST_API void* lantern_Tensor_renorm_tensor_scalar_intt_scalar(void* self, void* p, void* dim, void* maxnorm) { void* ret = _lantern_Tensor_renorm_tensor_scalar_intt_scalar(self, p, dim, maxnorm); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_unfold_tensor_intt_intt_intt)(void* self, void* dimension, void* size, void* step);
  HOST_API void* lantern_Tensor_unfold_tensor_intt_intt_intt(void* self, void* dimension, void* size, void* step) { void* ret = _lantern_Tensor_unfold_tensor_intt_intt_intt(self, dimension, size, step); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_equal_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_equal_tensor_tensor(void* self, void* other) { void* ret = _lantern_equal_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_equal_tensor_tensor)(void* self, void* other);
  HOST_API void* lantern_Tensor_equal_tensor_tensor(void* self, void* other) { void* ret = _lantern_Tensor_equal_tensor_tensor(self, other); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_out_tensor_tensor_tensor)(void* out, void* self, void* exponent);
  HOST_API void* lantern_pow_out_tensor_tensor_tensor(void* out, void* self, void* exponent) { void* ret = _lantern_pow_out_tensor_tensor_tensor(out, self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_tensor_tensor)(void* self, void* exponent);
  HOST_API void* lantern_pow_tensor_tensor(void* self, void* exponent) { void* ret = _lantern_pow_tensor_tensor(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_pow_tensor_tensor)(void* self, void* exponent);
  HOST_API void* lantern_Tensor_pow_tensor_tensor(void* self, void* exponent) { void* ret = _lantern_Tensor_pow_tensor_tensor(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_out_tensor_scalar_tensor)(void* out, void* self, void* exponent);
  HOST_API void* lantern_pow_out_tensor_scalar_tensor(void* out, void* self, void* exponent) { void* ret = _lantern_pow_out_tensor_scalar_tensor(out, self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_pow_scalar_tensor)(void* self, void* exponent);
  HOST_API void* lantern_pow_scalar_tensor(void* self, void* exponent) { void* ret = _lantern_pow_scalar_tensor(self, exponent); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_normal__tensor_double_double_generator)(void* self, void* mean, void* std, void* generator);
  HOST_API void* lantern_Tensor_normal__tensor_double_double_generator(void* self, void* mean, void* std, void* generator) { void* ret = _lantern_Tensor_normal__tensor_double_double_generator(self, mean, std, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_normal_out_tensor_tensor_double_generator)(void* out, void* mean, void* std, void* generator);
  HOST_API void* lantern_normal_out_tensor_tensor_double_generator(void* out, void* mean, void* std, void* generator) { void* ret = _lantern_normal_out_tensor_tensor_double_generator(out, mean, std, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_normal_out_tensor_double_tensor_generator)(void* out, void* mean, void* std, void* generator);
  HOST_API void* lantern_normal_out_tensor_double_tensor_generator(void* out, void* mean, void* std, void* generator) { void* ret = _lantern_normal_out_tensor_double_tensor_generator(out, mean, std, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_normal_out_tensor_tensor_tensor_generator)(void* out, void* mean, void* std, void* generator);
  HOST_API void* lantern_normal_out_tensor_tensor_tensor_generator(void* out, void* mean, void* std, void* generator) { void* ret = _lantern_normal_out_tensor_tensor_tensor_generator(out, mean, std, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_normal_out_tensor_double_double_intarrayref_generator)(void* out, void* mean, void* std, void* size, void* generator);
  HOST_API void* lantern_normal_out_tensor_double_double_intarrayref_generator(void* out, void* mean, void* std, void* size, void* generator) { void* ret = _lantern_normal_out_tensor_double_double_intarrayref_generator(out, mean, std, size, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_alias_tensor)(void* self);
  HOST_API void* lantern_alias_tensor(void* self) { void* ret = _lantern_alias_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_Tensor_alias_tensor)(void* self);
  HOST_API void* lantern_Tensor_alias_tensor(void* self) { void* ret = _lantern_Tensor_alias_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__addr_tensor_tensor_tensor_scalar_scalar)(void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern__addr_tensor_tensor_tensor_scalar_scalar(void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern__addr_tensor_tensor_tensor_scalar_scalar(self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__addr__tensor_tensor_tensor_scalar_scalar)(void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern__addr__tensor_tensor_tensor_scalar_scalar(void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern__addr__tensor_tensor_tensor_scalar_scalar(self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__addr_out_tensor_tensor_tensor_tensor_scalar_scalar)(void* out, void* self, void* vec1, void* vec2, void* beta, void* alpha);
  HOST_API void* lantern__addr_out_tensor_tensor_tensor_tensor_scalar_scalar(void* out, void* self, void* vec1, void* vec2, void* beta, void* alpha) { void* ret = _lantern__addr_out_tensor_tensor_tensor_tensor_scalar_scalar(out, self, vec1, vec2, beta, alpha); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__index_copy__tensor_intt_tensor_tensor)(void* self, void* dim, void* index, void* source);
  HOST_API void* lantern__index_copy__tensor_intt_tensor_tensor(void* self, void* dim, void* index, void* source) { void* ret = _lantern__index_copy__tensor_intt_tensor_tensor(self, dim, index, source); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cumsum_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern__cumsum_tensor_intt(void* self, void* dim) { void* ret = _lantern__cumsum_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cumsum_out_tensor_tensor_intt)(void* out, void* self, void* dim);
  HOST_API void* lantern__cumsum_out_tensor_tensor_intt(void* out, void* self, void* dim) { void* ret = _lantern__cumsum_out_tensor_tensor_intt(out, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cumprod_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern__cumprod_tensor_intt(void* self, void* dim) { void* ret = _lantern__cumprod_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cumprod_out_tensor_tensor_intt)(void* out, void* self, void* dim);
  HOST_API void* lantern__cumprod_out_tensor_tensor_intt(void* out, void* self, void* dim) { void* ret = _lantern__cumprod_out_tensor_tensor_intt(out, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__var_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern__var_tensor_bool(void* self, void* unbiased) { void* ret = _lantern__var_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__std_tensor_bool)(void* self, void* unbiased);
  HOST_API void* lantern__std_tensor_bool(void* self, void* unbiased) { void* ret = _lantern__std_tensor_bool(self, unbiased); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__amp_non_finite_check_and_unscale__tensor_tensor_tensor)(void* self, void* found_inf, void* inv_scale);
  HOST_API void* lantern__amp_non_finite_check_and_unscale__tensor_tensor_tensor(void* self, void* found_inf, void* inv_scale) { void* ret = _lantern__amp_non_finite_check_and_unscale__tensor_tensor_tensor(self, found_inf, inv_scale); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__amp_update_scale_tensor_tensor_tensor_double_double_intt)(void* growth_tracker, void* current_scale, void* found_inf, void* scale_growth_factor, void* scale_backoff_factor, void* growth_interval);
  HOST_API void* lantern__amp_update_scale_tensor_tensor_tensor_double_double_intt(void* growth_tracker, void* current_scale, void* found_inf, void* scale_growth_factor, void* scale_backoff_factor, void* growth_interval) { void* ret = _lantern__amp_update_scale_tensor_tensor_tensor_double_double_intt(growth_tracker, current_scale, found_inf, scale_growth_factor, scale_backoff_factor, growth_interval); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cat_tensorlist_intt)(void* tensors, void* dim);
  HOST_API void* lantern__cat_tensorlist_intt(void* tensors, void* dim) { void* ret = _lantern__cat_tensorlist_intt(tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__cat_out_tensor_tensorlist_intt)(void* out, void* tensors, void* dim);
  HOST_API void* lantern__cat_out_tensor_tensorlist_intt(void* out, void* tensors, void* dim) { void* ret = _lantern__cat_out_tensor_tensorlist_intt(out, tensors, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__mode_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern__mode_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern__mode_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__mode_out_tensor_tensor_tensor_intt_bool)(void* values, void* indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern__mode_out_tensor_tensor_tensor_intt_bool(void* values, void* indices, void* self, void* dim, void* keepdim) { void* ret = _lantern__mode_out_tensor_tensor_tensor_intt_bool(values, indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__max_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern__max_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern__max_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__max_out_tensor_tensor_tensor_intt_bool)(void* max, void* max_indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern__max_out_tensor_tensor_tensor_intt_bool(void* max, void* max_indices, void* self, void* dim, void* keepdim) { void* ret = _lantern__max_out_tensor_tensor_tensor_intt_bool(max, max_indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__min_tensor_intt_bool)(void* self, void* dim, void* keepdim);
  HOST_API void* lantern__min_tensor_intt_bool(void* self, void* dim, void* keepdim) { void* ret = _lantern__min_tensor_intt_bool(self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__min_out_tensor_tensor_tensor_intt_bool)(void* min, void* min_indices, void* self, void* dim, void* keepdim);
  HOST_API void* lantern__min_out_tensor_tensor_tensor_intt_bool(void* min, void* min_indices, void* self, void* dim, void* keepdim) { void* ret = _lantern__min_out_tensor_tensor_tensor_intt_bool(min, min_indices, self, dim, keepdim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mse_loss_out_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* reduction);
  HOST_API void* lantern_mse_loss_out_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* reduction) { void* ret = _lantern_mse_loss_out_tensor_tensor_tensor_intt(out, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mse_loss_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_mse_loss_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_mse_loss_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mse_loss_backward_out_tensor_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_mse_loss_backward_out_tensor_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_mse_loss_backward_out_tensor_tensor_tensor_tensor_intt(grad_input, grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mse_loss_backward_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_mse_loss_backward_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_mse_loss_backward_tensor_tensor_tensor_intt(grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_l1_loss_out_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* reduction);
  HOST_API void* lantern_l1_loss_out_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* reduction) { void* ret = _lantern_l1_loss_out_tensor_tensor_tensor_intt(out, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_l1_loss_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_l1_loss_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_l1_loss_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt(grad_input, grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_l1_loss_backward_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_l1_loss_backward_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_l1_loss_backward_tensor_tensor_tensor_intt(grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multi_margin_loss_out_tensor_tensor_tensor_scalar_scalar_tensor_intt)(void* out, void* self, void* target, void* p, void* margin, void* weight, void* reduction);
  HOST_API void* lantern_multi_margin_loss_out_tensor_tensor_tensor_scalar_scalar_tensor_intt(void* out, void* self, void* target, void* p, void* margin, void* weight, void* reduction) { void* ret = _lantern_multi_margin_loss_out_tensor_tensor_tensor_scalar_scalar_tensor_intt(out, self, target, p, margin, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multi_margin_loss_tensor_tensor_scalar_scalar_tensor_intt)(void* self, void* target, void* p, void* margin, void* weight, void* reduction);
  HOST_API void* lantern_multi_margin_loss_tensor_tensor_scalar_scalar_tensor_intt(void* self, void* target, void* p, void* margin, void* weight, void* reduction) { void* ret = _lantern_multi_margin_loss_tensor_tensor_scalar_scalar_tensor_intt(self, target, p, margin, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multi_margin_loss_backward_out_tensor_tensor_tensor_tensor_scalar_scalar_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* p, void* margin, void* weight, void* reduction);
  HOST_API void* lantern_multi_margin_loss_backward_out_tensor_tensor_tensor_tensor_scalar_scalar_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* p, void* margin, void* weight, void* reduction) { void* ret = _lantern_multi_margin_loss_backward_out_tensor_tensor_tensor_tensor_scalar_scalar_tensor_intt(grad_input, grad_output, self, target, p, margin, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multi_margin_loss_backward_tensor_tensor_tensor_scalar_scalar_tensor_intt)(void* grad_output, void* self, void* target, void* p, void* margin, void* weight, void* reduction);
  HOST_API void* lantern_multi_margin_loss_backward_tensor_tensor_tensor_scalar_scalar_tensor_intt(void* grad_output, void* self, void* target, void* p, void* margin, void* weight, void* reduction) { void* ret = _lantern_multi_margin_loss_backward_tensor_tensor_tensor_scalar_scalar_tensor_intt(grad_output, self, target, p, margin, weight, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_out_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* reduction);
  HOST_API void* lantern_multilabel_margin_loss_out_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* reduction) { void* ret = _lantern_multilabel_margin_loss_out_tensor_tensor_tensor_intt(out, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_multilabel_margin_loss_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_multilabel_margin_loss_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_forward_out_tensor_tensor_tensor_tensor_intt)(void* output, void* is_target, void* self, void* target, void* reduction);
  HOST_API void* lantern_multilabel_margin_loss_forward_out_tensor_tensor_tensor_tensor_intt(void* output, void* is_target, void* self, void* target, void* reduction) { void* ret = _lantern_multilabel_margin_loss_forward_out_tensor_tensor_tensor_tensor_intt(output, is_target, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_forward_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_multilabel_margin_loss_forward_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_multilabel_margin_loss_forward_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt_tensor)(void* grad_input, void* grad_output, void* self, void* target, void* reduction, void* is_target);
  HOST_API void* lantern_multilabel_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt_tensor(void* grad_input, void* grad_output, void* self, void* target, void* reduction, void* is_target) { void* ret = _lantern_multilabel_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt_tensor(grad_input, grad_output, self, target, reduction, is_target); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_multilabel_margin_loss_backward_tensor_tensor_tensor_intt_tensor)(void* grad_output, void* self, void* target, void* reduction, void* is_target);
  HOST_API void* lantern_multilabel_margin_loss_backward_tensor_tensor_tensor_intt_tensor(void* grad_output, void* self, void* target, void* reduction, void* is_target) { void* ret = _lantern_multilabel_margin_loss_backward_tensor_tensor_tensor_intt_tensor(grad_output, self, target, reduction, is_target); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_out_tensor_tensor_tensor_tensor_intt_intt)(void* out, void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss_out_tensor_tensor_tensor_tensor_intt_intt(void* out, void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss_out_tensor_tensor_tensor_tensor_intt_intt(out, self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_tensor_tensor_tensor_intt_intt)(void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss_tensor_tensor_tensor_intt_intt(void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss_tensor_tensor_tensor_intt_intt(self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt)(void* output, void* total_weight, void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt(void* output, void* total_weight, void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt(output, total_weight, self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_forward_tensor_tensor_tensor_intt_intt)(void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss_forward_tensor_tensor_tensor_intt_intt(void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss_forward_tensor_tensor_tensor_intt_intt(self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor)(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight);
  HOST_API void* lantern_nll_loss_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight) { void* ret = _lantern_nll_loss_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor(grad_input, grad_output, self, target, weight, reduction, ignore_index, total_weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss_backward_tensor_tensor_tensor_tensor_intt_intt_tensor)(void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight);
  HOST_API void* lantern_nll_loss_backward_tensor_tensor_tensor_tensor_intt_intt_tensor(void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight) { void* ret = _lantern_nll_loss_backward_tensor_tensor_tensor_tensor_intt_intt_tensor(grad_output, self, target, weight, reduction, ignore_index, total_weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_out_tensor_tensor_tensor_tensor_intt_intt)(void* out, void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss2d_out_tensor_tensor_tensor_tensor_intt_intt(void* out, void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss2d_out_tensor_tensor_tensor_tensor_intt_intt(out, self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_tensor_tensor_tensor_intt_intt)(void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss2d_tensor_tensor_tensor_intt_intt(void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss2d_tensor_tensor_tensor_intt_intt(self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt)(void* output, void* total_weight, void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss2d_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt(void* output, void* total_weight, void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss2d_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt(output, total_weight, self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_forward_tensor_tensor_tensor_intt_intt)(void* self, void* target, void* weight, void* reduction, void* ignore_index);
  HOST_API void* lantern_nll_loss2d_forward_tensor_tensor_tensor_intt_intt(void* self, void* target, void* weight, void* reduction, void* ignore_index) { void* ret = _lantern_nll_loss2d_forward_tensor_tensor_tensor_intt_intt(self, target, weight, reduction, ignore_index); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor)(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight);
  HOST_API void* lantern_nll_loss2d_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor(void* grad_input, void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight) { void* ret = _lantern_nll_loss2d_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor(grad_input, grad_output, self, target, weight, reduction, ignore_index, total_weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_nll_loss2d_backward_tensor_tensor_tensor_tensor_intt_intt_tensor)(void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight);
  HOST_API void* lantern_nll_loss2d_backward_tensor_tensor_tensor_tensor_intt_intt_tensor(void* grad_output, void* self, void* target, void* weight, void* reduction, void* ignore_index, void* total_weight) { void* ret = _lantern_nll_loss2d_backward_tensor_tensor_tensor_tensor_intt_intt_tensor(grad_output, self, target, weight, reduction, ignore_index, total_weight); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_smooth_l1_loss_out_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* reduction);
  HOST_API void* lantern_smooth_l1_loss_out_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* reduction) { void* ret = _lantern_smooth_l1_loss_out_tensor_tensor_tensor_intt(out, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_smooth_l1_loss_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_smooth_l1_loss_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_smooth_l1_loss_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_smooth_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_smooth_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_smooth_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt(grad_input, grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_smooth_l1_loss_backward_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_smooth_l1_loss_backward_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_smooth_l1_loss_backward_tensor_tensor_tensor_intt(grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_soft_margin_loss_out_tensor_tensor_tensor_intt)(void* out, void* self, void* target, void* reduction);
  HOST_API void* lantern_soft_margin_loss_out_tensor_tensor_tensor_intt(void* out, void* self, void* target, void* reduction) { void* ret = _lantern_soft_margin_loss_out_tensor_tensor_tensor_intt(out, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_soft_margin_loss_tensor_tensor_intt)(void* self, void* target, void* reduction);
  HOST_API void* lantern_soft_margin_loss_tensor_tensor_intt(void* self, void* target, void* reduction) { void* ret = _lantern_soft_margin_loss_tensor_tensor_intt(self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_soft_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_soft_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_soft_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt(grad_input, grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_soft_margin_loss_backward_tensor_tensor_tensor_intt)(void* grad_output, void* self, void* target, void* reduction);
  HOST_API void* lantern_soft_margin_loss_backward_tensor_tensor_tensor_intt(void* grad_output, void* self, void* target, void* reduction) { void* ret = _lantern_soft_margin_loss_backward_tensor_tensor_tensor_intt(grad_output, self, target, reduction); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_elu_out_tensor_tensor_scalar_scalar_scalar)(void* out, void* self, void* alpha, void* scale, void* input_scale);
  HOST_API void* lantern_elu_out_tensor_tensor_scalar_scalar_scalar(void* out, void* self, void* alpha, void* scale, void* input_scale) { void* ret = _lantern_elu_out_tensor_tensor_scalar_scalar_scalar(out, self, alpha, scale, input_scale); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_elu_tensor_scalar_scalar_scalar)(void* self, void* alpha, void* scale, void* input_scale);
  HOST_API void* lantern_elu_tensor_scalar_scalar_scalar(void* self, void* alpha, void* scale, void* input_scale) { void* ret = _lantern_elu_tensor_scalar_scalar_scalar(self, alpha, scale, input_scale); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_elu_backward_out_tensor_tensor_scalar_scalar_scalar_tensor)(void* grad_input, void* grad_output, void* alpha, void* scale, void* input_scale, void* output);
  HOST_API void* lantern_elu_backward_out_tensor_tensor_scalar_scalar_scalar_tensor(void* grad_input, void* grad_output, void* alpha, void* scale, void* input_scale, void* output) { void* ret = _lantern_elu_backward_out_tensor_tensor_scalar_scalar_scalar_tensor(grad_input, grad_output, alpha, scale, input_scale, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_elu_backward_tensor_scalar_scalar_scalar_tensor)(void* grad_output, void* alpha, void* scale, void* input_scale, void* output);
  HOST_API void* lantern_elu_backward_tensor_scalar_scalar_scalar_tensor(void* grad_output, void* alpha, void* scale, void* input_scale, void* output) { void* ret = _lantern_elu_backward_tensor_scalar_scalar_scalar_tensor(grad_output, alpha, scale, input_scale, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_elu__tensor_scalar_scalar_scalar)(void* self, void* alpha, void* scale, void* input_scale);
  HOST_API void* lantern_elu__tensor_scalar_scalar_scalar(void* self, void* alpha, void* scale, void* input_scale) { void* ret = _lantern_elu__tensor_scalar_scalar_scalar(self, alpha, scale, input_scale); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_glu_out_tensor_tensor_intt)(void* out, void* self, void* dim);
  HOST_API void* lantern_glu_out_tensor_tensor_intt(void* out, void* self, void* dim) { void* ret = _lantern_glu_out_tensor_tensor_intt(out, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_glu_tensor_intt)(void* self, void* dim);
  HOST_API void* lantern_glu_tensor_intt(void* self, void* dim) { void* ret = _lantern_glu_tensor_intt(self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_glu_backward_out_tensor_tensor_tensor_intt)(void* grad_input, void* grad_output, void* self, void* dim);
  HOST_API void* lantern_glu_backward_out_tensor_tensor_tensor_intt(void* grad_input, void* grad_output, void* self, void* dim) { void* ret = _lantern_glu_backward_out_tensor_tensor_tensor_intt(grad_input, grad_output, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_glu_backward_tensor_tensor_intt)(void* grad_output, void* self, void* dim);
  HOST_API void* lantern_glu_backward_tensor_tensor_intt(void* grad_output, void* self, void* dim) { void* ret = _lantern_glu_backward_tensor_tensor_intt(grad_output, self, dim); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardsigmoid_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_hardsigmoid_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_hardsigmoid_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardsigmoid_tensor)(void* self);
  HOST_API void* lantern_hardsigmoid_tensor(void* self) { void* ret = _lantern_hardsigmoid_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardsigmoid__tensor)(void* self);
  HOST_API void* lantern_hardsigmoid__tensor(void* self) { void* ret = _lantern_hardsigmoid__tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardsigmoid_backward_tensor_tensor)(void* grad_output, void* self);
  HOST_API void* lantern_hardsigmoid_backward_tensor_tensor(void* grad_output, void* self) { void* ret = _lantern_hardsigmoid_backward_tensor_tensor(grad_output, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardtanh_out_tensor_tensor_scalar_scalar)(void* out, void* self, void* min_val, void* max_val);
  HOST_API void* lantern_hardtanh_out_tensor_tensor_scalar_scalar(void* out, void* self, void* min_val, void* max_val) { void* ret = _lantern_hardtanh_out_tensor_tensor_scalar_scalar(out, self, min_val, max_val); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardtanh_tensor_scalar_scalar)(void* self, void* min_val, void* max_val);
  HOST_API void* lantern_hardtanh_tensor_scalar_scalar(void* self, void* min_val, void* max_val) { void* ret = _lantern_hardtanh_tensor_scalar_scalar(self, min_val, max_val); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardtanh_backward_out_tensor_tensor_tensor_scalar_scalar)(void* grad_input, void* grad_output, void* self, void* min_val, void* max_val);
  HOST_API void* lantern_hardtanh_backward_out_tensor_tensor_tensor_scalar_scalar(void* grad_input, void* grad_output, void* self, void* min_val, void* max_val) { void* ret = _lantern_hardtanh_backward_out_tensor_tensor_tensor_scalar_scalar(grad_input, grad_output, self, min_val, max_val); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardtanh_backward_tensor_tensor_scalar_scalar)(void* grad_output, void* self, void* min_val, void* max_val);
  HOST_API void* lantern_hardtanh_backward_tensor_tensor_scalar_scalar(void* grad_output, void* self, void* min_val, void* max_val) { void* ret = _lantern_hardtanh_backward_tensor_tensor_scalar_scalar(grad_output, self, min_val, max_val); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_hardtanh__tensor_scalar_scalar)(void* self, void* min_val, void* max_val);
  HOST_API void* lantern_hardtanh__tensor_scalar_scalar(void* self, void* min_val, void* max_val) { void* ret = _lantern_hardtanh__tensor_scalar_scalar(self, min_val, max_val); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_leaky_relu_out_tensor_tensor_scalar)(void* out, void* self, void* negative_slope);
  HOST_API void* lantern_leaky_relu_out_tensor_tensor_scalar(void* out, void* self, void* negative_slope) { void* ret = _lantern_leaky_relu_out_tensor_tensor_scalar(out, self, negative_slope); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_leaky_relu_tensor_scalar)(void* self, void* negative_slope);
  HOST_API void* lantern_leaky_relu_tensor_scalar(void* self, void* negative_slope) { void* ret = _lantern_leaky_relu_tensor_scalar(self, negative_slope); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_leaky_relu_backward_tensor_tensor_scalar_bool)(void* grad_output, void* self, void* negative_slope, void* self_is_result);
  HOST_API void* lantern_leaky_relu_backward_tensor_tensor_scalar_bool(void* grad_output, void* self, void* negative_slope, void* self_is_result) { void* ret = _lantern_leaky_relu_backward_tensor_tensor_scalar_bool(grad_output, self, negative_slope, self_is_result); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_leaky_relu__tensor_scalar)(void* self, void* negative_slope);
  HOST_API void* lantern_leaky_relu__tensor_scalar(void* self, void* negative_slope) { void* ret = _lantern_leaky_relu__tensor_scalar(self, negative_slope); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_out_tensor_tensor)(void* out, void* self);
  HOST_API void* lantern_log_sigmoid_out_tensor_tensor(void* out, void* self) { void* ret = _lantern_log_sigmoid_out_tensor_tensor(out, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_tensor)(void* self);
  HOST_API void* lantern_log_sigmoid_tensor(void* self) { void* ret = _lantern_log_sigmoid_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_forward_out_tensor_tensor_tensor)(void* output, void* buffer, void* self);
  HOST_API void* lantern_log_sigmoid_forward_out_tensor_tensor_tensor(void* output, void* buffer, void* self) { void* ret = _lantern_log_sigmoid_forward_out_tensor_tensor_tensor(output, buffer, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_forward_tensor)(void* self);
  HOST_API void* lantern_log_sigmoid_forward_tensor(void* self) { void* ret = _lantern_log_sigmoid_forward_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_backward_out_tensor_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* self, void* buffer);
  HOST_API void* lantern_log_sigmoid_backward_out_tensor_tensor_tensor_tensor(void* grad_input, void* grad_output, void* self, void* buffer) { void* ret = _lantern_log_sigmoid_backward_out_tensor_tensor_tensor_tensor(grad_input, grad_output, self, buffer); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_log_sigmoid_backward_tensor_tensor_tensor)(void* grad_output, void* self, void* buffer);
  HOST_API void* lantern_log_sigmoid_backward_tensor_tensor_tensor(void* grad_output, void* self, void* buffer) { void* ret = _lantern_log_sigmoid_backward_tensor_tensor_tensor(grad_output, self, buffer); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu_with_noise_out_tensor_tensor_tensor_scalar_scalar_bool_generator)(void* out, void* self, void* noise, void* lower, void* upper, void* training, void* generator);
  HOST_API void* lantern_rrelu_with_noise_out_tensor_tensor_tensor_scalar_scalar_bool_generator(void* out, void* self, void* noise, void* lower, void* upper, void* training, void* generator) { void* ret = _lantern_rrelu_with_noise_out_tensor_tensor_tensor_scalar_scalar_bool_generator(out, self, noise, lower, upper, training, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu_with_noise_tensor_tensor_scalar_scalar_bool_generator)(void* self, void* noise, void* lower, void* upper, void* training, void* generator);
  HOST_API void* lantern_rrelu_with_noise_tensor_tensor_scalar_scalar_bool_generator(void* self, void* noise, void* lower, void* upper, void* training, void* generator) { void* ret = _lantern_rrelu_with_noise_tensor_tensor_scalar_scalar_bool_generator(self, noise, lower, upper, training, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu_with_noise_backward_tensor_tensor_tensor_scalar_scalar_bool_bool)(void* grad_output, void* self, void* noise, void* lower, void* upper, void* training, void* self_is_result);
  HOST_API void* lantern_rrelu_with_noise_backward_tensor_tensor_tensor_scalar_scalar_bool_bool(void* grad_output, void* self, void* noise, void* lower, void* upper, void* training, void* self_is_result) { void* ret = _lantern_rrelu_with_noise_backward_tensor_tensor_tensor_scalar_scalar_bool_bool(grad_output, self, noise, lower, upper, training, self_is_result); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_rrelu_with_noise__tensor_tensor_scalar_scalar_bool_generator)(void* self, void* noise, void* lower, void* upper, void* training, void* generator);
  HOST_API void* lantern_rrelu_with_noise__tensor_tensor_scalar_scalar_bool_generator(void* self, void* noise, void* lower, void* upper, void* training, void* generator) { void* ret = _lantern_rrelu_with_noise__tensor_tensor_scalar_scalar_bool_generator(self, noise, lower, upper, training, generator); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softplus_out_tensor_tensor_scalar_scalar)(void* out, void* self, void* beta, void* threshold);
  HOST_API void* lantern_softplus_out_tensor_tensor_scalar_scalar(void* out, void* self, void* beta, void* threshold) { void* ret = _lantern_softplus_out_tensor_tensor_scalar_scalar(out, self, beta, threshold); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softplus_tensor_scalar_scalar)(void* self, void* beta, void* threshold);
  HOST_API void* lantern_softplus_tensor_scalar_scalar(void* self, void* beta, void* threshold) { void* ret = _lantern_softplus_tensor_scalar_scalar(self, beta, threshold); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softplus_backward_out_tensor_tensor_tensor_scalar_scalar_tensor)(void* grad_input, void* grad_output, void* self, void* beta, void* threshold, void* output);
  HOST_API void* lantern_softplus_backward_out_tensor_tensor_tensor_scalar_scalar_tensor(void* grad_input, void* grad_output, void* self, void* beta, void* threshold, void* output) { void* ret = _lantern_softplus_backward_out_tensor_tensor_tensor_scalar_scalar_tensor(grad_input, grad_output, self, beta, threshold, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softplus_backward_tensor_tensor_scalar_scalar_tensor)(void* grad_output, void* self, void* beta, void* threshold, void* output);
  HOST_API void* lantern_softplus_backward_tensor_tensor_scalar_scalar_tensor(void* grad_output, void* self, void* beta, void* threshold, void* output) { void* ret = _lantern_softplus_backward_tensor_tensor_scalar_scalar_tensor(grad_output, self, beta, threshold, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softshrink_out_tensor_tensor_scalar)(void* out, void* self, void* lambd);
  HOST_API void* lantern_softshrink_out_tensor_tensor_scalar(void* out, void* self, void* lambd) { void* ret = _lantern_softshrink_out_tensor_tensor_scalar(out, self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softshrink_tensor_scalar)(void* self, void* lambd);
  HOST_API void* lantern_softshrink_tensor_scalar(void* self, void* lambd) { void* ret = _lantern_softshrink_tensor_scalar(self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softshrink_backward_out_tensor_tensor_tensor_scalar)(void* grad_input, void* grad_output, void* self, void* lambd);
  HOST_API void* lantern_softshrink_backward_out_tensor_tensor_tensor_scalar(void* grad_input, void* grad_output, void* self, void* lambd) { void* ret = _lantern_softshrink_backward_out_tensor_tensor_tensor_scalar(grad_input, grad_output, self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_softshrink_backward_tensor_tensor_scalar)(void* grad_output, void* self, void* lambd);
  HOST_API void* lantern_softshrink_backward_tensor_tensor_scalar(void* grad_output, void* self, void* lambd) { void* ret = _lantern_softshrink_backward_tensor_tensor_scalar(grad_output, self, lambd); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool2d_out_tensor_tensor_intarrayref)(void* out, void* self, void* output_size);
  HOST_API void* lantern_adaptive_avg_pool2d_out_tensor_tensor_intarrayref(void* out, void* self, void* output_size) { void* ret = _lantern_adaptive_avg_pool2d_out_tensor_tensor_intarrayref(out, self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool2d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_avg_pool2d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_avg_pool2d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_mkldnn_adaptive_avg_pool2d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_mkldnn_adaptive_avg_pool2d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_mkldnn_adaptive_avg_pool2d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__adaptive_avg_pool2d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern__adaptive_avg_pool2d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern__adaptive_avg_pool2d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern__adaptive_avg_pool2d_backward_tensor_tensor)(void* grad_output, void* self);
  HOST_API void* lantern__adaptive_avg_pool2d_backward_tensor_tensor(void* grad_output, void* self) { void* ret = _lantern__adaptive_avg_pool2d_backward_tensor_tensor(grad_output, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool3d_out_tensor_tensor_intarrayref)(void* out, void* self, void* output_size);
  HOST_API void* lantern_adaptive_avg_pool3d_out_tensor_tensor_intarrayref(void* out, void* self, void* output_size) { void* ret = _lantern_adaptive_avg_pool3d_out_tensor_tensor_intarrayref(out, self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool3d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_avg_pool3d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_avg_pool3d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool3d_backward_out_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* self);
  HOST_API void* lantern_adaptive_avg_pool3d_backward_out_tensor_tensor_tensor(void* grad_input, void* grad_output, void* self) { void* ret = _lantern_adaptive_avg_pool3d_backward_out_tensor_tensor_tensor(grad_input, grad_output, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_avg_pool3d_backward_tensor_tensor)(void* grad_output, void* self);
  HOST_API void* lantern_adaptive_avg_pool3d_backward_tensor_tensor(void* grad_output, void* self) { void* ret = _lantern_adaptive_avg_pool3d_backward_tensor_tensor(grad_output, self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool2d_out_tensor_tensor_tensor_intarrayref)(void* out, void* indices, void* self, void* output_size);
  HOST_API void* lantern_adaptive_max_pool2d_out_tensor_tensor_tensor_intarrayref(void* out, void* indices, void* self, void* output_size) { void* ret = _lantern_adaptive_max_pool2d_out_tensor_tensor_tensor_intarrayref(out, indices, self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool2d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_max_pool2d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_max_pool2d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool2d_backward_out_tensor_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* self, void* indices);
  HOST_API void* lantern_adaptive_max_pool2d_backward_out_tensor_tensor_tensor_tensor(void* grad_input, void* grad_output, void* self, void* indices) { void* ret = _lantern_adaptive_max_pool2d_backward_out_tensor_tensor_tensor_tensor(grad_input, grad_output, self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool2d_backward_tensor_tensor_tensor)(void* grad_output, void* self, void* indices);
  HOST_API void* lantern_adaptive_max_pool2d_backward_tensor_tensor_tensor(void* grad_output, void* self, void* indices) { void* ret = _lantern_adaptive_max_pool2d_backward_tensor_tensor_tensor(grad_output, self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool3d_out_tensor_tensor_tensor_intarrayref)(void* out, void* indices, void* self, void* output_size);
  HOST_API void* lantern_adaptive_max_pool3d_out_tensor_tensor_tensor_intarrayref(void* out, void* indices, void* self, void* output_size) { void* ret = _lantern_adaptive_max_pool3d_out_tensor_tensor_tensor_intarrayref(out, indices, self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool3d_tensor_intarrayref)(void* self, void* output_size);
  HOST_API void* lantern_adaptive_max_pool3d_tensor_intarrayref(void* self, void* output_size) { void* ret = _lantern_adaptive_max_pool3d_tensor_intarrayref(self, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool3d_backward_out_tensor_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* self, void* indices);
  HOST_API void* lantern_adaptive_max_pool3d_backward_out_tensor_tensor_tensor_tensor(void* grad_input, void* grad_output, void* self, void* indices) { void* ret = _lantern_adaptive_max_pool3d_backward_out_tensor_tensor_tensor_tensor(grad_input, grad_output, self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_adaptive_max_pool3d_backward_tensor_tensor_tensor)(void* grad_output, void* self, void* indices);
  HOST_API void* lantern_adaptive_max_pool3d_backward_tensor_tensor_tensor(void* grad_output, void* self, void* indices) { void* ret = _lantern_adaptive_max_pool3d_backward_tensor_tensor_tensor(grad_output, self, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool2d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* out, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool2d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* out, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool2d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(out, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool2d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool2d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool2d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(grad_input, grad_output, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool2d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool2d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool2d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(grad_output, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool3d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* out, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool3d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* out, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool3d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(out, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool3d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool3d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool3d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(grad_input, grad_output, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_avg_pool3d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override);
  HOST_API void* lantern_avg_pool3d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* ceil_mode, void* count_include_pad, void* divisor_override) { void* ret = _lantern_avg_pool3d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt(grad_output, self, kernel_size, stride, padding, ceil_mode, count_include_pad, divisor_override); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool2d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)(void* output, void* indices, void* self, void* kernel_size, void* output_size, void* random_samples);
  HOST_API void* lantern_fractional_max_pool2d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(void* output, void* indices, void* self, void* kernel_size, void* output_size, void* random_samples) { void* ret = _lantern_fractional_max_pool2d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(output, indices, self, kernel_size, output_size, random_samples); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool2d_tensor_intarrayref_intarrayref_tensor)(void* self, void* kernel_size, void* output_size, void* random_samples);
  HOST_API void* lantern_fractional_max_pool2d_tensor_intarrayref_intarrayref_tensor(void* self, void* kernel_size, void* output_size, void* random_samples) { void* ret = _lantern_fractional_max_pool2d_tensor_intarrayref_intarrayref_tensor(self, kernel_size, output_size, random_samples); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* output_size, void* indices);
  HOST_API void* lantern_fractional_max_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(void* grad_input, void* grad_output, void* self, void* kernel_size, void* output_size, void* indices) { void* ret = _lantern_fractional_max_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(grad_input, grad_output, self, kernel_size, output_size, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool2d_backward_tensor_tensor_intarrayref_intarrayref_tensor)(void* grad_output, void* self, void* kernel_size, void* output_size, void* indices);
  HOST_API void* lantern_fractional_max_pool2d_backward_tensor_tensor_intarrayref_intarrayref_tensor(void* grad_output, void* self, void* kernel_size, void* output_size, void* indices) { void* ret = _lantern_fractional_max_pool2d_backward_tensor_tensor_intarrayref_intarrayref_tensor(grad_output, self, kernel_size, output_size, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)(void* output, void* indices, void* self, void* kernel_size, void* output_size, void* random_samples);
  HOST_API void* lantern_fractional_max_pool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(void* output, void* indices, void* self, void* kernel_size, void* output_size, void* random_samples) { void* ret = _lantern_fractional_max_pool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(output, indices, self, kernel_size, output_size, random_samples); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool3d_tensor_intarrayref_intarrayref_tensor)(void* self, void* kernel_size, void* output_size, void* random_samples);
  HOST_API void* lantern_fractional_max_pool3d_tensor_intarrayref_intarrayref_tensor(void* self, void* kernel_size, void* output_size, void* random_samples) { void* ret = _lantern_fractional_max_pool3d_tensor_intarrayref_intarrayref_tensor(self, kernel_size, output_size, random_samples); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* output_size, void* indices);
  HOST_API void* lantern_fractional_max_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(void* grad_input, void* grad_output, void* self, void* kernel_size, void* output_size, void* indices) { void* ret = _lantern_fractional_max_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor(grad_input, grad_output, self, kernel_size, output_size, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_fractional_max_pool3d_backward_tensor_tensor_intarrayref_intarrayref_tensor)(void* grad_output, void* self, void* kernel_size, void* output_size, void* indices);
  HOST_API void* lantern_fractional_max_pool3d_backward_tensor_tensor_intarrayref_intarrayref_tensor(void* grad_output, void* self, void* kernel_size, void* output_size, void* indices) { void* ret = _lantern_fractional_max_pool3d_backward_tensor_tensor_intarrayref_intarrayref_tensor(grad_output, self, kernel_size, output_size, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool2d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* out, void* indices, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool2d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* out, void* indices, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool2d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(out, indices, self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool2d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool2d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool2d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool2d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices);
  HOST_API void* lantern_max_pool2d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices) { void* ret = _lantern_max_pool2d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(grad_input, grad_output, self, kernel_size, stride, padding, dilation, ceil_mode, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool2d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices);
  HOST_API void* lantern_max_pool2d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices) { void* ret = _lantern_max_pool2d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(grad_output, self, kernel_size, stride, padding, dilation, ceil_mode, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool3d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* out, void* indices, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool3d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* out, void* indices, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool3d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(out, indices, self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool3d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode);
  HOST_API void* lantern_max_pool3d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode) { void* ret = _lantern_max_pool3d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool(self, kernel_size, stride, padding, dilation, ceil_mode); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool3d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices);
  HOST_API void* lantern_max_pool3d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(void* grad_input, void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices) { void* ret = _lantern_max_pool3d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(grad_input, grad_output, self, kernel_size, stride, padding, dilation, ceil_mode, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_pool3d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices);
  HOST_API void* lantern_max_pool3d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(void* grad_output, void* self, void* kernel_size, void* stride, void* padding, void* dilation, void* ceil_mode, void* indices) { void* ret = _lantern_max_pool3d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor(grad_output, self, kernel_size, stride, padding, dilation, ceil_mode, indices); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool2d_out_tensor_tensor_tensor_intarrayref)(void* out, void* self, void* indices, void* output_size);
  HOST_API void* lantern_max_unpool2d_out_tensor_tensor_tensor_intarrayref(void* out, void* self, void* indices, void* output_size) { void* ret = _lantern_max_unpool2d_out_tensor_tensor_tensor_intarrayref(out, self, indices, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool2d_tensor_tensor_intarrayref)(void* self, void* indices, void* output_size);
  HOST_API void* lantern_max_unpool2d_tensor_tensor_intarrayref(void* self, void* indices, void* output_size) { void* ret = _lantern_max_unpool2d_tensor_tensor_intarrayref(self, indices, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool2d_backward_out_tensor_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* indices, void* output_size);
  HOST_API void* lantern_max_unpool2d_backward_out_tensor_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* indices, void* output_size) { void* ret = _lantern_max_unpool2d_backward_out_tensor_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, indices, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool2d_backward_tensor_tensor_tensor_intarrayref)(void* grad_output, void* self, void* indices, void* output_size);
  HOST_API void* lantern_max_unpool2d_backward_tensor_tensor_tensor_intarrayref(void* grad_output, void* self, void* indices, void* output_size) { void* ret = _lantern_max_unpool2d_backward_tensor_tensor_tensor_intarrayref(grad_output, self, indices, output_size); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* indices, void* output_size, void* stride, void* padding);
  HOST_API void* lantern_max_unpool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(void* out, void* self, void* indices, void* output_size, void* stride, void* padding) { void* ret = _lantern_max_unpool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(out, self, indices, output_size, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool3d_tensor_tensor_intarrayref_intarrayref_intarrayref)(void* self, void* indices, void* output_size, void* stride, void* padding);
  HOST_API void* lantern_max_unpool3d_tensor_tensor_intarrayref_intarrayref_intarrayref(void* self, void* indices, void* output_size, void* stride, void* padding) { void* ret = _lantern_max_unpool3d_tensor_tensor_intarrayref_intarrayref_intarrayref(self, indices, output_size, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool3d_backward_out_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)(void* grad_input, void* grad_output, void* self, void* indices, void* output_size, void* stride, void* padding);
  HOST_API void* lantern_max_unpool3d_backward_out_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(void* grad_input, void* grad_output, void* self, void* indices, void* output_size, void* stride, void* padding) { void* ret = _lantern_max_unpool3d_backward_out_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(grad_input, grad_output, self, indices, output_size, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_max_unpool3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)(void* grad_output, void* self, void* indices, void* output_size, void* stride, void* padding);
  HOST_API void* lantern_max_unpool3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(void* grad_output, void* self, void* indices, void* output_size, void* stride, void* padding) { void* ret = _lantern_max_unpool3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref(grad_output, self, indices, output_size, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad1d_out_tensor_tensor_intarrayref)(void* out, void* self, void* padding);
  HOST_API void* lantern_reflection_pad1d_out_tensor_tensor_intarrayref(void* out, void* self, void* padding) { void* ret = _lantern_reflection_pad1d_out_tensor_tensor_intarrayref(out, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad1d_tensor_intarrayref)(void* self, void* padding);
  HOST_API void* lantern_reflection_pad1d_tensor_intarrayref(void* self, void* padding) { void* ret = _lantern_reflection_pad1d_tensor_intarrayref(self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad1d_backward_out_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* padding);
  HOST_API void* lantern_reflection_pad1d_backward_out_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* padding) { void* ret = _lantern_reflection_pad1d_backward_out_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad1d_backward_tensor_tensor_intarrayref)(void* grad_output, void* self, void* padding);
  HOST_API void* lantern_reflection_pad1d_backward_tensor_tensor_intarrayref(void* grad_output, void* self, void* padding) { void* ret = _lantern_reflection_pad1d_backward_tensor_tensor_intarrayref(grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad2d_out_tensor_tensor_intarrayref)(void* out, void* self, void* padding);
  HOST_API void* lantern_reflection_pad2d_out_tensor_tensor_intarrayref(void* out, void* self, void* padding) { void* ret = _lantern_reflection_pad2d_out_tensor_tensor_intarrayref(out, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad2d_tensor_intarrayref)(void* self, void* padding);
  HOST_API void* lantern_reflection_pad2d_tensor_intarrayref(void* self, void* padding) { void* ret = _lantern_reflection_pad2d_tensor_intarrayref(self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad2d_backward_out_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* padding);
  HOST_API void* lantern_reflection_pad2d_backward_out_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* padding) { void* ret = _lantern_reflection_pad2d_backward_out_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_reflection_pad2d_backward_tensor_tensor_intarrayref)(void* grad_output, void* self, void* padding);
  HOST_API void* lantern_reflection_pad2d_backward_tensor_tensor_intarrayref(void* grad_output, void* self, void* padding) { void* ret = _lantern_reflection_pad2d_backward_tensor_tensor_intarrayref(grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad1d_out_tensor_tensor_intarrayref)(void* out, void* self, void* padding);
  HOST_API void* lantern_replication_pad1d_out_tensor_tensor_intarrayref(void* out, void* self, void* padding) { void* ret = _lantern_replication_pad1d_out_tensor_tensor_intarrayref(out, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad1d_tensor_intarrayref)(void* self, void* padding);
  HOST_API void* lantern_replication_pad1d_tensor_intarrayref(void* self, void* padding) { void* ret = _lantern_replication_pad1d_tensor_intarrayref(self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad1d_backward_out_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad1d_backward_out_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad1d_backward_out_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad1d_backward_tensor_tensor_intarrayref)(void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad1d_backward_tensor_tensor_intarrayref(void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad1d_backward_tensor_tensor_intarrayref(grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad2d_out_tensor_tensor_intarrayref)(void* out, void* self, void* padding);
  HOST_API void* lantern_replication_pad2d_out_tensor_tensor_intarrayref(void* out, void* self, void* padding) { void* ret = _lantern_replication_pad2d_out_tensor_tensor_intarrayref(out, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad2d_tensor_intarrayref)(void* self, void* padding);
  HOST_API void* lantern_replication_pad2d_tensor_intarrayref(void* self, void* padding) { void* ret = _lantern_replication_pad2d_tensor_intarrayref(self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad2d_backward_out_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad2d_backward_out_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad2d_backward_out_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad2d_backward_tensor_tensor_intarrayref)(void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad2d_backward_tensor_tensor_intarrayref(void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad2d_backward_tensor_tensor_intarrayref(grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad3d_out_tensor_tensor_intarrayref)(void* out, void* self, void* padding);
  HOST_API void* lantern_replication_pad3d_out_tensor_tensor_intarrayref(void* out, void* self, void* padding) { void* ret = _lantern_replication_pad3d_out_tensor_tensor_intarrayref(out, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad3d_tensor_intarrayref)(void* self, void* padding);
  HOST_API void* lantern_replication_pad3d_tensor_intarrayref(void* self, void* padding) { void* ret = _lantern_replication_pad3d_tensor_intarrayref(self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad3d_backward_out_tensor_tensor_tensor_intarrayref)(void* grad_input, void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad3d_backward_out_tensor_tensor_tensor_intarrayref(void* grad_input, void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad3d_backward_out_tensor_tensor_tensor_intarrayref(grad_input, grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_replication_pad3d_backward_tensor_tensor_intarrayref)(void* grad_output, void* self, void* padding);
  HOST_API void* lantern_replication_pad3d_backward_tensor_tensor_intarrayref(void* grad_output, void* self, void* padding) { void* ret = _lantern_replication_pad3d_backward_tensor_tensor_intarrayref(grad_output, self, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_linear1d_out_tensor_tensor_intarrayref_bool_double)(void* out, void* self, void* output_size, void* align_corners, void* scales);
  HOST_API void* lantern_upsample_linear1d_out_tensor_tensor_intarrayref_bool_double(void* out, void* self, void* output_size, void* align_corners, void* scales) { void* ret = _lantern_upsample_linear1d_out_tensor_tensor_intarrayref_bool_double(out, self, output_size, align_corners, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_linear1d_tensor_intarrayref_bool_double)(void* self, void* output_size, void* align_corners, void* scales);
  HOST_API void* lantern_upsample_linear1d_tensor_intarrayref_bool_double(void* self, void* output_size, void* align_corners, void* scales) { void* ret = _lantern_upsample_linear1d_tensor_intarrayref_bool_double(self, output_size, align_corners, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_linear1d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales);
  HOST_API void* lantern_upsample_linear1d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales) { void* ret = _lantern_upsample_linear1d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double(grad_input, grad_output, output_size, input_size, align_corners, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_linear1d_backward_tensor_intarrayref_intarrayref_bool_double)(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales);
  HOST_API void* lantern_upsample_linear1d_backward_tensor_intarrayref_intarrayref_bool_double(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales) { void* ret = _lantern_upsample_linear1d_backward_tensor_intarrayref_intarrayref_bool_double(grad_output, output_size, input_size, align_corners, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bilinear2d_out_tensor_tensor_intarrayref_bool_double_double)(void* out, void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bilinear2d_out_tensor_tensor_intarrayref_bool_double_double(void* out, void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bilinear2d_out_tensor_tensor_intarrayref_bool_double_double(out, self, output_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bilinear2d_tensor_intarrayref_bool_double_double)(void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bilinear2d_tensor_intarrayref_bool_double_double(void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bilinear2d_tensor_intarrayref_bool_double_double(self, output_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bilinear2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bilinear2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bilinear2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double(grad_input, grad_output, output_size, input_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bilinear2d_backward_tensor_intarrayref_intarrayref_bool_double_double)(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bilinear2d_backward_tensor_intarrayref_intarrayref_bool_double_double(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bilinear2d_backward_tensor_intarrayref_intarrayref_bool_double_double(grad_output, output_size, input_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bicubic2d_out_tensor_tensor_intarrayref_bool_double_double)(void* out, void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bicubic2d_out_tensor_tensor_intarrayref_bool_double_double(void* out, void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bicubic2d_out_tensor_tensor_intarrayref_bool_double_double(out, self, output_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bicubic2d_tensor_intarrayref_bool_double_double)(void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bicubic2d_tensor_intarrayref_bool_double_double(void* self, void* output_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bicubic2d_tensor_intarrayref_bool_double_double(self, output_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bicubic2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bicubic2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bicubic2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double(grad_input, grad_output, output_size, input_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_bicubic2d_backward_tensor_intarrayref_intarrayref_bool_double_double)(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_bicubic2d_backward_tensor_intarrayref_intarrayref_bool_double_double(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_bicubic2d_backward_tensor_intarrayref_intarrayref_bool_double_double(grad_output, output_size, input_size, align_corners, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_trilinear3d_out_tensor_tensor_intarrayref_bool_double_double_double)(void* out, void* self, void* output_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_trilinear3d_out_tensor_tensor_intarrayref_bool_double_double_double(void* out, void* self, void* output_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_trilinear3d_out_tensor_tensor_intarrayref_bool_double_double_double(out, self, output_size, align_corners, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_trilinear3d_tensor_intarrayref_bool_double_double_double)(void* self, void* output_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_trilinear3d_tensor_intarrayref_bool_double_double_double(void* self, void* output_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_trilinear3d_tensor_intarrayref_bool_double_double_double(self, output_size, align_corners, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_trilinear3d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_trilinear3d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_trilinear3d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double_double(grad_input, grad_output, output_size, input_size, align_corners, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_trilinear3d_backward_tensor_intarrayref_intarrayref_bool_double_double_double)(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_trilinear3d_backward_tensor_intarrayref_intarrayref_bool_double_double_double(void* grad_output, void* output_size, void* input_size, void* align_corners, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_trilinear3d_backward_tensor_intarrayref_intarrayref_bool_double_double_double(grad_output, output_size, input_size, align_corners, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest1d_out_tensor_tensor_intarrayref_double)(void* out, void* self, void* output_size, void* scales);
  HOST_API void* lantern_upsample_nearest1d_out_tensor_tensor_intarrayref_double(void* out, void* self, void* output_size, void* scales) { void* ret = _lantern_upsample_nearest1d_out_tensor_tensor_intarrayref_double(out, self, output_size, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest1d_tensor_intarrayref_double)(void* self, void* output_size, void* scales);
  HOST_API void* lantern_upsample_nearest1d_tensor_intarrayref_double(void* self, void* output_size, void* scales) { void* ret = _lantern_upsample_nearest1d_tensor_intarrayref_double(self, output_size, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest1d_backward_out_tensor_tensor_intarrayref_intarrayref_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales);
  HOST_API void* lantern_upsample_nearest1d_backward_out_tensor_tensor_intarrayref_intarrayref_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales) { void* ret = _lantern_upsample_nearest1d_backward_out_tensor_tensor_intarrayref_intarrayref_double(grad_input, grad_output, output_size, input_size, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest1d_backward_tensor_intarrayref_intarrayref_double)(void* grad_output, void* output_size, void* input_size, void* scales);
  HOST_API void* lantern_upsample_nearest1d_backward_tensor_intarrayref_intarrayref_double(void* grad_output, void* output_size, void* input_size, void* scales) { void* ret = _lantern_upsample_nearest1d_backward_tensor_intarrayref_intarrayref_double(grad_output, output_size, input_size, scales); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest2d_out_tensor_tensor_intarrayref_double_double)(void* out, void* self, void* output_size, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest2d_out_tensor_tensor_intarrayref_double_double(void* out, void* self, void* output_size, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest2d_out_tensor_tensor_intarrayref_double_double(out, self, output_size, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest2d_tensor_intarrayref_double_double)(void* self, void* output_size, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest2d_tensor_intarrayref_double_double(void* self, void* output_size, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest2d_tensor_intarrayref_double_double(self, output_size, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest2d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest2d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest2d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double(grad_input, grad_output, output_size, input_size, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest2d_backward_tensor_intarrayref_intarrayref_double_double)(void* grad_output, void* output_size, void* input_size, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest2d_backward_tensor_intarrayref_intarrayref_double_double(void* grad_output, void* output_size, void* input_size, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest2d_backward_tensor_intarrayref_intarrayref_double_double(grad_output, output_size, input_size, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest3d_out_tensor_tensor_intarrayref_double_double_double)(void* out, void* self, void* output_size, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest3d_out_tensor_tensor_intarrayref_double_double_double(void* out, void* self, void* output_size, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest3d_out_tensor_tensor_intarrayref_double_double_double(out, self, output_size, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest3d_tensor_intarrayref_double_double_double)(void* self, void* output_size, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest3d_tensor_intarrayref_double_double_double(void* self, void* output_size, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest3d_tensor_intarrayref_double_double_double(self, output_size, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest3d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double_double)(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest3d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double_double(void* grad_input, void* grad_output, void* output_size, void* input_size, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest3d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double_double(grad_input, grad_output, output_size, input_size, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_upsample_nearest3d_backward_tensor_intarrayref_intarrayref_double_double_double)(void* grad_output, void* output_size, void* input_size, void* scales_d, void* scales_h, void* scales_w);
  HOST_API void* lantern_upsample_nearest3d_backward_tensor_intarrayref_intarrayref_double_double_double(void* grad_output, void* output_size, void* input_size, void* scales_d, void* scales_h, void* scales_w) { void* ret = _lantern_upsample_nearest3d_backward_tensor_intarrayref_intarrayref_double_double_double(grad_output, output_size, input_size, scales_d, scales_h, scales_w); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sigmoid_backward_out_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* output);
  HOST_API void* lantern_sigmoid_backward_out_tensor_tensor_tensor(void* grad_input, void* grad_output, void* output) { void* ret = _lantern_sigmoid_backward_out_tensor_tensor_tensor(grad_input, grad_output, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_sigmoid_backward_tensor_tensor)(void* grad_output, void* output);
  HOST_API void* lantern_sigmoid_backward_tensor_tensor(void* grad_output, void* output) { void* ret = _lantern_sigmoid_backward_tensor_tensor(grad_output, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tanh_backward_out_tensor_tensor_tensor)(void* grad_input, void* grad_output, void* output);
  HOST_API void* lantern_tanh_backward_out_tensor_tensor_tensor(void* grad_input, void* grad_output, void* output) { void* ret = _lantern_tanh_backward_out_tensor_tensor_tensor(grad_input, grad_output, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_tanh_backward_tensor_tensor)(void* grad_output, void* output);
  HOST_API void* lantern_tanh_backward_tensor_tensor(void* grad_output, void* output) { void* ret = _lantern_tanh_backward_tensor_tensor(grad_output, output); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation);
  HOST_API void* lantern_slow_conv_transpose2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation) { void* ret = _lantern_slow_conv_transpose2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding, output_padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation);
  HOST_API void* lantern_slow_conv_transpose2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation) { void* ret = _lantern_slow_conv_transpose2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, output_padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor)(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* columns, void* ones);
  HOST_API void* lantern_slow_conv_transpose2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* columns, void* ones) { void* ret = _lantern_slow_conv_transpose2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor(grad_input, grad_weight, grad_bias, grad_output, self, weight, kernel_size, stride, padding, output_padding, dilation, columns, ones); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* columns, void* ones, void* output_mask);
  HOST_API void* lantern_slow_conv_transpose2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* columns, void* ones, void* output_mask) { void* ret = _lantern_slow_conv_transpose2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, output_padding, dilation, columns, ones, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation);
  HOST_API void* lantern_slow_conv_transpose3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation) { void* ret = _lantern_slow_conv_transpose3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding, output_padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation);
  HOST_API void* lantern_slow_conv_transpose3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* output_padding, void* dilation) { void* ret = _lantern_slow_conv_transpose3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, output_padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor)(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* finput, void* fgrad_input);
  HOST_API void* lantern_slow_conv_transpose3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* finput, void* fgrad_input) { void* ret = _lantern_slow_conv_transpose3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor(grad_input, grad_weight, grad_bias, grad_output, self, weight, kernel_size, stride, padding, output_padding, dilation, finput, fgrad_input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_transpose3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* finput, void* fgrad_input, void* output_mask);
  HOST_API void* lantern_slow_conv_transpose3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* output_padding, void* dilation, void* finput, void* fgrad_input, void* output_mask) { void* ret = _lantern_slow_conv_transpose3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, output_padding, dilation, finput, fgrad_input, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_thnn_conv2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_thnn_conv2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_thnn_conv2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_thnn_conv2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* output, void* finput, void* fgrad_input, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_thnn_conv2d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* output, void* finput, void* fgrad_input, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_thnn_conv2d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(output, finput, fgrad_input, self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_thnn_conv2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_thnn_conv2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor)(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input);
  HOST_API void* lantern_thnn_conv2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input) { void* ret = _lantern_thnn_conv2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor(grad_input, grad_weight, grad_bias, grad_output, self, weight, kernel_size, stride, padding, finput, fgrad_input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input, void* output_mask);
  HOST_API void* lantern_thnn_conv2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input, void* output_mask) { void* ret = _lantern_thnn_conv2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, finput, fgrad_input, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_thnn_conv_depthwise2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_thnn_conv_depthwise2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_thnn_conv_depthwise2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_thnn_conv_depthwise2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_forward_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_thnn_conv_depthwise2d_forward_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_thnn_conv_depthwise2d_forward_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_thnn_conv_depthwise2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_thnn_conv_depthwise2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_backward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* grad_input, void* grad_weight, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_thnn_conv_depthwise2d_backward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* grad_input, void* grad_weight, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation) { void* ret = _lantern_thnn_conv_depthwise2d_backward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(grad_input, grad_weight, grad_output, self, weight, kernel_size, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_thnn_conv_depthwise2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask);
  HOST_API void* lantern_thnn_conv_depthwise2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask) { void* ret = _lantern_thnn_conv_depthwise2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, dilation, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_slow_conv3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* out, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_slow_conv3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(out, self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_slow_conv3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_slow_conv3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* output, void* finput, void* fgrad_input, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_slow_conv3d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* output, void* finput, void* fgrad_input, void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_slow_conv3d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(output, finput, fgrad_input, self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding);
  HOST_API void* lantern_slow_conv3d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding) { void* ret = _lantern_slow_conv3d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor)(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input);
  HOST_API void* lantern_slow_conv3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor(void* grad_input, void* grad_weight, void* grad_bias, void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input) { void* ret = _lantern_slow_conv3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor(grad_input, grad_weight, grad_bias, grad_output, self, weight, kernel_size, stride, padding, finput, fgrad_input); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input, void* output_mask);
  HOST_API void* lantern_slow_conv3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* finput, void* fgrad_input, void* output_mask) { void* ret = _lantern_slow_conv3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, finput, fgrad_input, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_dilated2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_slow_conv_dilated2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_slow_conv_dilated2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_dilated2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask);
  HOST_API void* lantern_slow_conv_dilated2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask) { void* ret = _lantern_slow_conv_dilated2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, dilation, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_dilated3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation);
  HOST_API void* lantern_slow_conv_dilated3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(void* self, void* weight, void* kernel_size, void* bias, void* stride, void* padding, void* dilation) { void* ret = _lantern_slow_conv_dilated3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref(self, weight, kernel_size, bias, stride, padding, dilation); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_slow_conv_dilated3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask);
  HOST_API void* lantern_slow_conv_dilated3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(void* grad_output, void* self, void* weight, void* kernel_size, void* stride, void* padding, void* dilation, void* output_mask) { void* ret = _lantern_slow_conv_dilated3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool(grad_output, self, weight, kernel_size, stride, padding, dilation, output_mask); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_col2im_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* output_size, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_col2im_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(void* out, void* self, void* output_size, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_col2im_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(out, self, output_size, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_col2im_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)(void* self, void* output_size, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_col2im_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(void* self, void* output_size, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_col2im_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(self, output_size, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_col2im_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* grad_input, void* grad_output, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_col2im_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* grad_input, void* grad_output, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_col2im_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(grad_input, grad_output, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_col2im_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* grad_output, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_col2im_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* grad_output, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_col2im_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref(grad_output, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_im2col_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* out, void* self, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_im2col_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* out, void* self, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_im2col_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref(out, self, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_im2col_tensor_intarrayref_intarrayref_intarrayref_intarrayref)(void* self, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_im2col_tensor_intarrayref_intarrayref_intarrayref_intarrayref(void* self, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_im2col_tensor_intarrayref_intarrayref_intarrayref_intarrayref(self, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_im2col_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)(void* grad_input, void* grad_output, void* input_size, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_im2col_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(void* grad_input, void* grad_output, void* input_size, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_im2col_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(grad_input, grad_output, input_size, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_im2col_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)(void* grad_output, void* input_size, void* kernel_size, void* dilation, void* padding, void* stride);
  HOST_API void* lantern_im2col_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(void* grad_output, void* input_size, void* kernel_size, void* dilation, void* padding, void* stride) { void* ret = _lantern_im2col_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref(grad_output, input_size, kernel_size, dilation, padding, stride); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_isfinite_tensor)(void* self);
  HOST_API void* lantern_isfinite_tensor(void* self) { void* ret = _lantern_isfinite_tensor(self); LANTERN_HOST_HANDLER return ret; }
  LANTERN_API void* (LANTERN_PTR _lantern_isinf_tensor)(void* self);
  HOST_API void* lantern_isinf_tensor(void* self) { void* ret = _lantern_isinf_tensor(self); LANTERN_HOST_HANDLER return ret; }
  /* Autogen Headers -- End */

#ifdef __cplusplus
}
#endif

#ifndef LANTERN_HEADERS_ONLY

#include <string>

inline const char *pathSeparator()
{
#ifdef _WIN32
  return "\\";
#else
  return "/";
#endif
}

inline const char *libraryName()
{
#ifdef __APPLE__
  return "liblantern.dylib";
#else
#ifdef _WIN32
  return "lantern.dll";
#else
  return "liblantern.so";
#endif
#endif
}

void *pLibrary = NULL;

#define LOAD_SYMBOL(name)                                         \
  if (!laternLoadSymbol(pLibrary, #name, (void **)&name, pError))  \
    return false;

void lanternLoadError(std::string *pError)
{
#ifdef _WIN32
  LPVOID lpMsgBuf;
  DWORD dw = ::GetLastError();

  DWORD length = ::FormatMessage(
      FORMAT_MESSAGE_ALLOCATE_BUFFER |
          FORMAT_MESSAGE_FROM_SYSTEM |
          FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      dw,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPTSTR)&lpMsgBuf,
      0, NULL);

  if (length != 0)
  {
    std::string msg((LPTSTR)lpMsgBuf);
    LocalFree(lpMsgBuf);
    pError->assign(msg);
  }
  else
  {
    pError->assign("Unknown error");
  }
#else
  const char *msg = ::dlerror();
  if (msg != NULL)
    pError->assign(msg);
  else
    pError->assign("Unknown error");
#endif
}

bool lanternLoadLibrary(const std::string &libPath, std::string *pError)
{
  pLibrary = NULL;

  char lastLibChar = libPath.at(libPath.size() - 1);
  std::string separator = (lastLibChar == '/' || lastLibChar == '\\') ? "" : pathSeparator();
  std::string libFile = libPath + separator + libraryName();

#ifdef _WIN32

  typedef DLL_DIRECTORY_COOKIE(WINAPI * PAddDllDirectory)(PCWSTR);
  HMODULE hKernel = ::GetModuleHandle("kernel32.dll");

  if (hKernel == NULL)
  {
    lanternLoadError(pError);
    *pError = "Get Kernel - " + *pError;
    return false;
  }

  PAddDllDirectory add_dll_directory = (PAddDllDirectory)::GetProcAddress(hKernel, "AddDllDirectory");

  if (add_dll_directory != NULL)
  {
    std::wstring libPathWStr = std::wstring(libPath.begin(), libPath.end());
    DLL_DIRECTORY_COOKIE cookie = add_dll_directory(libPathWStr.c_str());

    if (cookie == NULL)
    {
      lanternLoadError(pError);
      *pError = "Add Dll Directory - " + *pError;
      return false;
    }
  }

  pLibrary = (void *)::LoadLibraryEx(libFile.c_str(), NULL, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
#else
  pLibrary = ::dlopen(libFile.c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif
  if (pLibrary == NULL)
  {
    lanternLoadError(pError);
    *pError = libFile + " - " + *pError;
    return false;
  }
  else
  {
    return true;
  }
}

bool laternLoadSymbol(void *pLib, const std::string &name, void **ppSymbol, std::string *pError)
{
  *ppSymbol = NULL;
#ifdef _WIN32
  *ppSymbol = (void *)::GetProcAddress((HINSTANCE)pLib, name.c_str());
#else
  *ppSymbol = ::dlsym(pLib, name.c_str());
#endif
  if (*ppSymbol == NULL)
  {
    lanternLoadError(pError);
    *pError = name + " - " + *pError;
    return false;
  }
  else
  {
    return true;
  }
}

bool laternCloseLibrary(void *pLib, std::string *pError)
{
#ifdef _WIN32
  if (!::FreeLibrary((HMODULE)pLib))
#else
  if (::dlclose(pLib) != 0)
#endif
  {
    lanternLoadError(pError);
    return false;
  }
  else
  {
    return true;
  }
}

bool lanternInit(const std::string &libPath, std::string *pError)
{
  if (!lanternLoadLibrary(libPath, pError))
    return false;

  LOAD_SYMBOL(lanternConfigure);
  LOAD_SYMBOL(lanternVersion);
  LOAD_SYMBOL(lanternSetLastError);
  LOAD_SYMBOL(lanternLastErrorClear);
  LOAD_SYMBOL(lanternLastError);
  LOAD_SYMBOL(lanternTest);
  LOAD_SYMBOL(_lantern_Device);
  LOAD_SYMBOL(_lantern_Device_type);
  LOAD_SYMBOL(_lantern_Device_index);
  LOAD_SYMBOL(_lantern_from_blob);
  LOAD_SYMBOL(_lantern_Tensor_StreamInsertion);
  LOAD_SYMBOL(_lantern_TensorOptions);
  LOAD_SYMBOL(_lantern_TensorOptions_dtype);
  LOAD_SYMBOL(_lantern_TensorOptions_device);
  LOAD_SYMBOL(_lantern_TensorOptions_layout);
  LOAD_SYMBOL(_lantern_TensorOptions_requires_grad);
  LOAD_SYMBOL(_lantern_TensorOptions_pinned_memory);
  LOAD_SYMBOL(_lantern_Dtype_float32);
  LOAD_SYMBOL(_lantern_Dtype_float64);
  LOAD_SYMBOL(_lantern_Dtype_float16);
  LOAD_SYMBOL(_lantern_Dtype_uint8);
  LOAD_SYMBOL(_lantern_Dtype_int8);
  LOAD_SYMBOL(_lantern_Dtype_int16);
  LOAD_SYMBOL(_lantern_Dtype_int32);
  LOAD_SYMBOL(_lantern_Dtype_int64);
  LOAD_SYMBOL(_lantern_Dtype_bool);
  LOAD_SYMBOL(_lantern_Dtype_type);
  LOAD_SYMBOL(_lantern_vector_int64_t);
  LOAD_SYMBOL(_lantern_IntArrayRef);
  LOAD_SYMBOL(_lantern_MemoryFormat_Contiguous);
  LOAD_SYMBOL(_lantern_MemoryFormat_Preserve);
  LOAD_SYMBOL(_lantern_MemoryFormat_ChannelsLast);
  LOAD_SYMBOL(_lantern_MemoryFormat_type);
  LOAD_SYMBOL(_lantern_Tensor_clone);
  LOAD_SYMBOL(_lantern_Tensor_permute);
  LOAD_SYMBOL(_lantern_Tensor_contiguous);
  LOAD_SYMBOL(_lantern_Tensor_to);
  LOAD_SYMBOL(_lantern_Tensor_set_requires_grad);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_double);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_uint8_t);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_int32_t);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_int16_t);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_bool);
  LOAD_SYMBOL(_lantern_Tensor_numel);
  LOAD_SYMBOL(_lantern_Tensor_ndimension);
  LOAD_SYMBOL(_lantern_Tensor_size);
  LOAD_SYMBOL(_lantern_Tensor_dtype);
  LOAD_SYMBOL(_lantern_Generator);
  LOAD_SYMBOL(_lantern_Generator_current_seed);
  LOAD_SYMBOL(_lantern_Generator_set_current_seed);
  LOAD_SYMBOL(_lantern_QScheme_per_channel_affine);
  LOAD_SYMBOL(_lantern_QScheme_per_tensor_affine);
  LOAD_SYMBOL(_lantern_QScheme_per_channel_symmetric);
  LOAD_SYMBOL(_lantern_QScheme_per_tensor_symmetric);
  LOAD_SYMBOL(_lantern_QScheme_type);
  LOAD_SYMBOL(_lantern_TensorList);
  LOAD_SYMBOL(_lantern_TensorList_push_back);
  LOAD_SYMBOL(_lantern_TensorList_at);
  LOAD_SYMBOL(_lantern_TensorList_size);
  LOAD_SYMBOL(_lantern_Scalar);
  LOAD_SYMBOL(_lantern_vector_get);
  LOAD_SYMBOL(_lantern_int);
  LOAD_SYMBOL(_lantern_int64_t);
  LOAD_SYMBOL(_lantern_bool);
  LOAD_SYMBOL(_lantern_Dimname);
  LOAD_SYMBOL(_lantern_DimnameList);
  LOAD_SYMBOL(_lantern_DimnameList_push_back);
  LOAD_SYMBOL(_lantern_Dimname_to_string);
  LOAD_SYMBOL(_lantern_DimnameList_size);
  LOAD_SYMBOL(_lantern_DimnameList_at);
  LOAD_SYMBOL(_lantern_Scalar_nullopt);
  LOAD_SYMBOL(_lantern_Tensor_delete);
  LOAD_SYMBOL(_lantern_bool_delete);
  LOAD_SYMBOL(_lantern_int64_t_delete);
  LOAD_SYMBOL(_lantern_TensorList_delete);
  LOAD_SYMBOL(_lantern_double_delete);
  LOAD_SYMBOL(_lantern_QScheme_delete);
  LOAD_SYMBOL(_lantern_Scalar_delete);
  LOAD_SYMBOL(_lantern_ScalarType_delete);
  LOAD_SYMBOL(_lantern_Dtype_delete);
  LOAD_SYMBOL(_lantern_TensorOptions_delete);
  LOAD_SYMBOL(_lantern_Device_delete);
  LOAD_SYMBOL(_lantern_Layout_delete);
  LOAD_SYMBOL(_lantern_TensorOptions_print);
  LOAD_SYMBOL(_lantern_TensorOptions_address);
  LOAD_SYMBOL(_lantern_Generator_delete);
  LOAD_SYMBOL(_lantern_Dimname_delete);
  LOAD_SYMBOL(_lantern_DimnameList_delete);
  LOAD_SYMBOL(_lantern_MemoryFormat_delete);
  LOAD_SYMBOL(_lantern_Reduction_Sum);
  LOAD_SYMBOL(_lantern_Reduction_None);
  LOAD_SYMBOL(_lantern_Reduction_Mean);
  LOAD_SYMBOL(_lantern_double);
  LOAD_SYMBOL(_lantern_Dtype_quint8);
  LOAD_SYMBOL(_lantern_Dtype_qint8);
  LOAD_SYMBOL(_lantern_Dtype_qint32);
  LOAD_SYMBOL(_lantern_Tensor_is_quantized);
  LOAD_SYMBOL(_lantern_autograd_set_grad_mode);
  LOAD_SYMBOL(_lantern_Tensor_undefined);
  LOAD_SYMBOL(_lantern_Tensor_grad);
  LOAD_SYMBOL(_lantern_Tensor_requires_grad);
  LOAD_SYMBOL(_lantern_Tensor_register_hook);
  LOAD_SYMBOL(_lantern_new_hook);
  LOAD_SYMBOL(_lantern_Tensor_remove_hook);
  LOAD_SYMBOL(_lantern_variable_list_new);
  LOAD_SYMBOL(_lantern_variable_list_push_back);
  LOAD_SYMBOL(_lantern_variable_list_get);
  LOAD_SYMBOL(_lantern_variable_list_delete);
  LOAD_SYMBOL(_lantern_variable_list_size);
  LOAD_SYMBOL(_lantern_Function_lambda);
  LOAD_SYMBOL(_lantern_Function_apply);
  LOAD_SYMBOL(_lantern_AutogradContext_save_for_backward);
  LOAD_SYMBOL(_lantern_AutogradContext_get_saved_variables);
  LOAD_SYMBOL(_lantern_vector_string_new);
  LOAD_SYMBOL(_lantern_vector_string_push_back);
  LOAD_SYMBOL(_lantern_vector_string_size);
  LOAD_SYMBOL(_lantern_vector_string_at);
  LOAD_SYMBOL(_lantern_vector_bool_new);
  LOAD_SYMBOL(_lantern_vector_bool_push_back);
  LOAD_SYMBOL(_lantern_vector_bool_size);
  LOAD_SYMBOL(_lantern_vector_bool_at);
  LOAD_SYMBOL(_lantern_AutogradContext_set_arguments);
  LOAD_SYMBOL(_lantern_AutogradContext_get_argument_names);
  LOAD_SYMBOL(_lantern_AutogradContext_get_argument_needs_grad);
  LOAD_SYMBOL(_lantern_AutogradContext_set_saved_variables_names);
  LOAD_SYMBOL(_lantern_AutogradContext_get_saved_variables_names);
  LOAD_SYMBOL(_lantern_AutogradContext_mark_dirty);
  LOAD_SYMBOL(_lantern_AutogradContext_mark_non_differentiable);
  LOAD_SYMBOL(_lantern_optional_double);
  LOAD_SYMBOL(_test_grad_fn);
  LOAD_SYMBOL(_lantern_Tensor_grad_fn);
  LOAD_SYMBOL(_lantern_Node_name);
  LOAD_SYMBOL(_lantern_Node_next_edges);
  LOAD_SYMBOL(_lantern_edge_list_size);
  LOAD_SYMBOL(_lantern_edge_list_at);
  LOAD_SYMBOL(_lantern_Edge_function);
  LOAD_SYMBOL(_lantern_vector_int64_t_delete);
  LOAD_SYMBOL(_lantern_autograd_backward);
  LOAD_SYMBOL(_lantern_autograd_grad);
  LOAD_SYMBOL(_lantern_Layout_strided);
  LOAD_SYMBOL(_lantern_Layout_sparse);
  LOAD_SYMBOL(_lantern_Layout_string);
  LOAD_SYMBOL(_lantern_TensorIndex_new);
  LOAD_SYMBOL(_lantern_TensorIndex_append_tensor);
  LOAD_SYMBOL(_lantern_TensorIndex_append_ellipsis);
  LOAD_SYMBOL(_lantern_TensorIndex_append_slice);
  LOAD_SYMBOL(_lantern_TensorIndex_append_none);
  LOAD_SYMBOL(_lantern_TensorIndex_append_bool);
  LOAD_SYMBOL(_lantern_TensorIndex_append_int64);
  LOAD_SYMBOL(_lantern_Tensor_index);
  LOAD_SYMBOL(_lantern_TensorIndex_delete);
  LOAD_SYMBOL(_lantern_Slice);
  LOAD_SYMBOL(_lantern_optional_int64_t);
  LOAD_SYMBOL(_lantern_Slice_delete);
  LOAD_SYMBOL(_lantern_optional_int64_t_delete);
  LOAD_SYMBOL(_lantern_Tensor_device);
  LOAD_SYMBOL(_lantern_cuda_is_available);
  LOAD_SYMBOL(_lantern_cuda_device_count);
  LOAD_SYMBOL(_lantern_cuda_current_device);
  LOAD_SYMBOL(_lantern_cuda_show_config);
  LOAD_SYMBOL(_lantern_nn_utils_rnn_pack_padded_sequence);
  LOAD_SYMBOL(_lantern_PackedSequence_delete);
  LOAD_SYMBOL(_lantern_nn_utils_PackedSequence_data);
  LOAD_SYMBOL(_lantern_nn_utils_PackedSequence_batch_sizes);
  LOAD_SYMBOL(_lantern_nn_utils_PackedSequence_sorted_indices);
  LOAD_SYMBOL(_lantern_nn_utils_PackedSequence_unsorted_indices);
  LOAD_SYMBOL(_lantern_nn_utils_rnn_pack_sequence);
  LOAD_SYMBOL(_lantern_nn_utils_rnn_pad_packed_sequence);
  LOAD_SYMBOL(_lantern_nn_utils_rnn_pad_sequence);
  LOAD_SYMBOL(_lantern_nn_utils_rnn_PackedSequence_new);
  LOAD_SYMBOL(_lantern_Scalar_dtype);
  LOAD_SYMBOL(_lantern_Scalar_to_float);
  LOAD_SYMBOL(_lantern_Scalar_to_int);
  LOAD_SYMBOL(_lantern_Scalar_to_double);
  LOAD_SYMBOL(_lantern_Scalar_to_bool);
  LOAD_SYMBOL(_lantern_Tensor_is_undefined);
  LOAD_SYMBOL(_lantern_set_default_dtype);
  LOAD_SYMBOL(_lantern_get_default_dtype);
  LOAD_SYMBOL(_lantern_Tensor_set_grad_);
  LOAD_SYMBOL(_lantern_Tensor_storage);
  LOAD_SYMBOL(_lantern_Tensor_has_storage);
  LOAD_SYMBOL(_lantern_Storage_data_ptr);
  LOAD_SYMBOL(_lantern_Storage_delete);
  LOAD_SYMBOL(_lantern_Tensor_is_contiguous);
  LOAD_SYMBOL(_lantern_tensor_save);
  LOAD_SYMBOL(_lantern_tensor_load);
  LOAD_SYMBOL(_lantern_test_tensor);
  LOAD_SYMBOL(_lantern_test_print);
  LOAD_SYMBOL(_lantern_tensor_serialized_size);
  LOAD_SYMBOL(_lantern_const_char_delete);
  LOAD_SYMBOL(_lantern_Tensor_index_put_tensor_);
  LOAD_SYMBOL(_lantern_Tensor_index_put_scalar_);
  LOAD_SYMBOL(_lantern_manual_seed);
  LOAD_SYMBOL(_lantern_load_state_dict);
  LOAD_SYMBOL(_lantern_get_state_dict_keys);
  LOAD_SYMBOL(_lantern_get_state_dict_values);
  LOAD_SYMBOL(_lantern_IValue_delete);
  LOAD_SYMBOL(_lantern_vector_string_delete);
  LOAD_SYMBOL(_lantern_Tensor_data_ptr_int64_t);
  LOAD_SYMBOL(_lantern_Tensor_has_names);
  LOAD_SYMBOL(_lantern_Tensor_names);
  LOAD_SYMBOL(_lantern_string_new);
  LOAD_SYMBOL(_lantern_string_delete);
  /* Autogen Symbols -- Start */
  LOAD_SYMBOL(_lantern__cast_byte_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_char_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_double_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_float_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_int_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_long_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_short_tensor_bool)
  LOAD_SYMBOL(_lantern__cast_half_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_backward_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_set_data_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_data_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_leaf_tensor)
  LOAD_SYMBOL(_lantern_Tensor_output_nr_tensor)
  LOAD_SYMBOL(_lantern_Tensor__version_tensor)
  LOAD_SYMBOL(_lantern_Tensor_requires_grad__tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_retain_grad_tensor)
  LOAD_SYMBOL(_lantern_Tensor_rename__tensor_dimnamelist)
  LOAD_SYMBOL(_lantern_Tensor_rename_tensor_dimnamelist)
  LOAD_SYMBOL(_lantern_Tensor_align_to_tensor_dimnamelist)
  LOAD_SYMBOL(_lantern_Tensor_align_to_tensor_dimnamelist_intt)
  LOAD_SYMBOL(_lantern_Tensor_align_as_tensor_tensor)
  LOAD_SYMBOL(_lantern_align_tensors_tensorlist)
  LOAD_SYMBOL(_lantern_Tensor_refine_names_tensor_dimnamelist)
  LOAD_SYMBOL(_lantern_Tensor_unflatten_tensor_dimname_intarrayref_dimnamelist)
  LOAD_SYMBOL(_lantern_Tensor_unflatten_tensor_intt_intarrayref_dimnamelist)
  LOAD_SYMBOL(_lantern__use_cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern__cudnn_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern__use_cudnn_rnn_flatten_weight)
  LOAD_SYMBOL(_lantern__cudnn_rnn_flatten_weight_tensorlist_intt_intt_intt_intt_intt_bool_bool)
  LOAD_SYMBOL(_lantern__cudnn_rnn_tensor_tensorlist_intt_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor)
  LOAD_SYMBOL(_lantern__cudnn_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern__cudnn_init_dropout_state_double_bool_intt_tensoroptions)
  LOAD_SYMBOL(_lantern__debug_has_internal_overlap_tensor)
  LOAD_SYMBOL(_lantern__fused_dropout_tensor_double_generator)
  LOAD_SYMBOL(_lantern__masked_scale_tensor_tensor_double)
  LOAD_SYMBOL(_lantern__sobol_engine_draw_tensor_intt_tensor_intt_intt_scalartype)
  LOAD_SYMBOL(_lantern__sobol_engine_ff__tensor_intt_tensor_intt_intt)
  LOAD_SYMBOL(_lantern__sobol_engine_scramble__tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__sobol_engine_initialize_state__tensor_intt)
  LOAD_SYMBOL(_lantern__reshape_from_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__shape_as_tensor_tensor)
  LOAD_SYMBOL(_lantern_dropout_tensor_double_bool)
  LOAD_SYMBOL(_lantern_dropout__tensor_double_bool)
  LOAD_SYMBOL(_lantern_feature_dropout_tensor_double_bool)
  LOAD_SYMBOL(_lantern_feature_dropout__tensor_double_bool)
  LOAD_SYMBOL(_lantern_alpha_dropout_tensor_double_bool)
  LOAD_SYMBOL(_lantern_alpha_dropout__tensor_double_bool)
  LOAD_SYMBOL(_lantern_feature_alpha_dropout_tensor_double_bool)
  LOAD_SYMBOL(_lantern_feature_alpha_dropout__tensor_double_bool)
  LOAD_SYMBOL(_lantern_abs_tensor)
  LOAD_SYMBOL(_lantern_Tensor_abs_tensor)
  LOAD_SYMBOL(_lantern_abs__tensor)
  LOAD_SYMBOL(_lantern_Tensor_abs__tensor)
  LOAD_SYMBOL(_lantern_abs_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_angle_tensor)
  LOAD_SYMBOL(_lantern_Tensor_angle_tensor)
  LOAD_SYMBOL(_lantern_angle_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_real_tensor)
  LOAD_SYMBOL(_lantern_imag_tensor)
  LOAD_SYMBOL(_lantern_conj_tensor)
  LOAD_SYMBOL(_lantern_Tensor_conj_tensor)
  LOAD_SYMBOL(_lantern_conj_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_acos_tensor)
  LOAD_SYMBOL(_lantern_Tensor_acos_tensor)
  LOAD_SYMBOL(_lantern_acos__tensor)
  LOAD_SYMBOL(_lantern_Tensor_acos__tensor)
  LOAD_SYMBOL(_lantern_acos_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_avg_pool1d_tensor_intarrayref_intarrayref_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool1d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_max_pool1d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_add_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_add_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_add__tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_add_out_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_add_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_add_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_add__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addmv_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addmv_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addmv__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addmv__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addmv_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addr_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addr_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addr__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addr_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_affine_grid_generator_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_affine_grid_generator_backward_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_all_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_all_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_all_out_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_all_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_all_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_all_out_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_allclose_tensor_tensor_double_double_bool)
  LOAD_SYMBOL(_lantern_Tensor_allclose_tensor_tensor_double_double_bool)
  LOAD_SYMBOL(_lantern_any_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_any_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_any_out_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_any_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_any_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_any_out_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_arange_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_arange_scalar_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_arange_scalar_scalar_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_arange_out_tensor_scalar)
  LOAD_SYMBOL(_lantern_arange_out_tensor_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern__dim_arange_tensor_intt)
  LOAD_SYMBOL(_lantern_argmax_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_argmax_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_argmin_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_argmin_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_as_strided_tensor_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_Tensor_as_strided_tensor_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_as_strided__tensor_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_Tensor_as_strided__tensor_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_asin_tensor)
  LOAD_SYMBOL(_lantern_Tensor_asin_tensor)
  LOAD_SYMBOL(_lantern_asin__tensor)
  LOAD_SYMBOL(_lantern_Tensor_asin__tensor)
  LOAD_SYMBOL(_lantern_asin_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_atan_tensor)
  LOAD_SYMBOL(_lantern_Tensor_atan_tensor)
  LOAD_SYMBOL(_lantern_atan__tensor)
  LOAD_SYMBOL(_lantern_Tensor_atan__tensor)
  LOAD_SYMBOL(_lantern_atan_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_baddbmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_baddbmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_baddbmm__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern__baddbmm_mkl__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_baddbmm_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_bartlett_window_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_bartlett_window_intt_bool_tensoroptions)
  LOAD_SYMBOL(_lantern_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)
  LOAD_SYMBOL(_lantern_quantized_batch_norm_tensor_tensor_tensor_tensor_tensor_double_double_intt)
  LOAD_SYMBOL(_lantern__batch_norm_impl_index_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)
  LOAD_SYMBOL(_lantern__batch_norm_impl_index_backward_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool_tensor)
  LOAD_SYMBOL(_lantern_bernoulli_tensor_generator)
  LOAD_SYMBOL(_lantern_Tensor_bernoulli_tensor_generator)
  LOAD_SYMBOL(_lantern_bernoulli_out_tensor_tensor_generator)
  LOAD_SYMBOL(_lantern_Tensor_bernoulli__tensor_tensor_generator)
  LOAD_SYMBOL(_lantern_Tensor_bernoulli__tensor_double_generator)
  LOAD_SYMBOL(_lantern_bernoulli_tensor_double_generator)
  LOAD_SYMBOL(_lantern_Tensor_bernoulli_tensor_double_generator)
  LOAD_SYMBOL(_lantern_bilinear_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_backward_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_backward_out_tensor_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_with_logits_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_binary_cross_entropy_with_logits_backward_tensor_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_bincount_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_bincount_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_bitwise_not_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_not_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_not__tensor)
  LOAD_SYMBOL(_lantern_bitwise_not_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_not_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_not_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_not__tensor)
  LOAD_SYMBOL(_lantern_logical_not_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_xor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_xor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_xor__tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_xor_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_and_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_and_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_and__tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_and_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_or_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_or_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logical_or__tensor_tensor)
  LOAD_SYMBOL(_lantern_logical_or_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_blackman_window_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_blackman_window_intt_bool_tensoroptions)
  LOAD_SYMBOL(_lantern_bmm_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bmm_tensor_tensor)
  LOAD_SYMBOL(_lantern_bmm_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_broadcast_tensors_tensorlist)
  LOAD_SYMBOL(_lantern_cat_tensorlist_intt)
  LOAD_SYMBOL(_lantern_cat_out_tensor_tensorlist_intt)
  LOAD_SYMBOL(_lantern_cat_tensorlist_dimname)
  LOAD_SYMBOL(_lantern_cat_out_tensor_tensorlist_dimname)
  LOAD_SYMBOL(_lantern_ceil_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ceil_tensor)
  LOAD_SYMBOL(_lantern_ceil__tensor)
  LOAD_SYMBOL(_lantern_Tensor_ceil__tensor)
  LOAD_SYMBOL(_lantern_ceil_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_chain_matmul_tensorlist)
  LOAD_SYMBOL(_lantern_chunk_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_chunk_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_clamp_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_clamp__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_clamp_out_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_clamp_max_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp_max_tensor_scalar)
  LOAD_SYMBOL(_lantern_clamp_max__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp_max__tensor_scalar)
  LOAD_SYMBOL(_lantern_clamp_max_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_clamp_min_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp_min_tensor_scalar)
  LOAD_SYMBOL(_lantern_clamp_min__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_clamp_min__tensor_scalar)
  LOAD_SYMBOL(_lantern_clamp_min_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_cudnn_is_acceptable_tensor)
  LOAD_SYMBOL(_lantern_constant_pad_nd_tensor_intarrayref_scalar)
  LOAD_SYMBOL(_lantern_Tensor_contiguous_tensor_memoryformat)
  LOAD_SYMBOL(_lantern_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt)
  LOAD_SYMBOL(_lantern_convolution_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt)
  LOAD_SYMBOL(_lantern_convolution_backward_overrideable_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_stdarraybool)
  LOAD_SYMBOL(_lantern__convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool)
  LOAD_SYMBOL(_lantern__convolution_nogroup_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref)
  LOAD_SYMBOL(_lantern__convolution_double_backward_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_intarrayref_intt_bool_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_conv1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_conv2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_conv3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_conv_tbc_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_conv_tbc_backward_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_conv_transpose1d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)
  LOAD_SYMBOL(_lantern_conv_transpose2d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)
  LOAD_SYMBOL(_lantern_conv_transpose3d_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_copy__tensor_tensor_bool)
  LOAD_SYMBOL(_lantern__copy_from_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_cos_tensor)
  LOAD_SYMBOL(_lantern_Tensor_cos_tensor)
  LOAD_SYMBOL(_lantern_cos__tensor)
  LOAD_SYMBOL(_lantern_Tensor_cos__tensor)
  LOAD_SYMBOL(_lantern_cos_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_cosh_tensor)
  LOAD_SYMBOL(_lantern_Tensor_cosh_tensor)
  LOAD_SYMBOL(_lantern_cosh__tensor)
  LOAD_SYMBOL(_lantern_Tensor_cosh__tensor)
  LOAD_SYMBOL(_lantern_cosh_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_cosine_embedding_loss_tensor_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern_cudnn_affine_grid_generator_tensor_intt_intt_intt_intt)
  LOAD_SYMBOL(_lantern_cudnn_affine_grid_generator_backward_tensor_intt_intt_intt_intt)
  LOAD_SYMBOL(_lantern_cudnn_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)
  LOAD_SYMBOL(_lantern_cudnn_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double_tensor)
  LOAD_SYMBOL(_lantern_cudnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_transpose_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_cudnn_grid_sampler_tensor_tensor)
  LOAD_SYMBOL(_lantern_cudnn_grid_sampler_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_cummax_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_cummax_tensor_intt)
  LOAD_SYMBOL(_lantern_cummax_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_cummax_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_cummax_tensor_dimname)
  LOAD_SYMBOL(_lantern_cummax_out_tensor_tensor_tensor_dimname)
  LOAD_SYMBOL(_lantern__cummax_helper_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_cummin_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_cummin_tensor_intt)
  LOAD_SYMBOL(_lantern_cummin_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_cummin_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_cummin_tensor_dimname)
  LOAD_SYMBOL(_lantern_cummin_out_tensor_tensor_tensor_dimname)
  LOAD_SYMBOL(_lantern__cummin_helper_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_cumprod_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_cumprod_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_cumprod_out_tensor_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_cumprod_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_cumprod_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_cumprod_out_tensor_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_cumsum_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_cumsum_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_cumsum_out_tensor_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_cumsum_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_cumsum_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_cumsum_out_tensor_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_intt_bool)
  LOAD_SYMBOL(_lantern_ctc_loss_tensor_tensor_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern__ctc_loss_tensor_tensor_intarrayref_intarrayref_intt_bool)
  LOAD_SYMBOL(_lantern__ctc_loss_backward_tensor_tensor_tensor_intarrayref_intarrayref_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_det_tensor)
  LOAD_SYMBOL(_lantern_Tensor_det_tensor)
  LOAD_SYMBOL(_lantern_diag_embed_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_diag_embed_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_diagflat_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_diagflat_tensor_intt)
  LOAD_SYMBOL(_lantern_diagonal_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_diagonal_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_diagonal_tensor_dimname_dimname_dimname_intt)
  LOAD_SYMBOL(_lantern_Tensor_diagonal_tensor_dimname_dimname_dimname_intt)
  LOAD_SYMBOL(_lantern_Tensor_fill_diagonal__tensor_scalar_bool)
  LOAD_SYMBOL(_lantern_div_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_div_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_div__tensor_tensor)
  LOAD_SYMBOL(_lantern_div_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_div_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_div_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_div__tensor_scalar)
  LOAD_SYMBOL(_lantern_dot_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_dot_tensor_tensor)
  LOAD_SYMBOL(_lantern_dot_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_einsum_stdstring_tensorlist)
  LOAD_SYMBOL(_lantern_embedding_tensor_tensor_intt_bool_bool)
  LOAD_SYMBOL(_lantern_embedding_backward_tensor_tensor_intt_intt_bool_bool)
  LOAD_SYMBOL(_lantern_embedding_dense_backward_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_embedding_renorm__tensor_tensor_double_double)
  LOAD_SYMBOL(_lantern_embedding_sparse_backward_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool)
  LOAD_SYMBOL(_lantern__embedding_bag_tensor_tensor_tensor_bool_intt_bool_tensor_bool)
  LOAD_SYMBOL(_lantern__embedding_bag_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_bool_tensor)
  LOAD_SYMBOL(_lantern__embedding_bag_sparse_backward_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor)
  LOAD_SYMBOL(_lantern__embedding_bag_dense_backward_tensor_tensor_tensor_tensor_tensor_tensor_intt_bool_intt_tensor)
  LOAD_SYMBOL(_lantern__embedding_bag_per_sample_weights_backward_tensor_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_empty_intarrayref_dimnamelist_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_empty_intarrayref_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_new_empty_tensor_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_Tensor_new_full_tensor_intarrayref_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_Tensor_new_zeros_tensor_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern__empty_affine_quantized_intarrayref_tensoroptions_double_intt_memoryformat)
  LOAD_SYMBOL(_lantern__empty_per_channel_affine_quantized_intarrayref_tensor_tensor_intt_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_resize__tensor_intarrayref_memoryformat)
  LOAD_SYMBOL(_lantern_empty_out_tensor_intarrayref_memoryformat)
  LOAD_SYMBOL(_lantern_empty_like_tensor_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_empty_strided_intarrayref_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_erf_tensor)
  LOAD_SYMBOL(_lantern_Tensor_erf_tensor)
  LOAD_SYMBOL(_lantern_erf__tensor)
  LOAD_SYMBOL(_lantern_Tensor_erf__tensor)
  LOAD_SYMBOL(_lantern_erf_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_erfc_tensor)
  LOAD_SYMBOL(_lantern_Tensor_erfc_tensor)
  LOAD_SYMBOL(_lantern_erfc__tensor)
  LOAD_SYMBOL(_lantern_Tensor_erfc__tensor)
  LOAD_SYMBOL(_lantern_erfc_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_exp_tensor)
  LOAD_SYMBOL(_lantern_Tensor_exp_tensor)
  LOAD_SYMBOL(_lantern_exp__tensor)
  LOAD_SYMBOL(_lantern_Tensor_exp__tensor)
  LOAD_SYMBOL(_lantern_exp_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_expm1_tensor)
  LOAD_SYMBOL(_lantern_Tensor_expm1_tensor)
  LOAD_SYMBOL(_lantern_expm1__tensor)
  LOAD_SYMBOL(_lantern_Tensor_expm1__tensor)
  LOAD_SYMBOL(_lantern_expm1_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_expand_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_Tensor_expand_as_tensor_tensor)
  LOAD_SYMBOL(_lantern_eye_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_eye_intt_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_eye_out_tensor_intt)
  LOAD_SYMBOL(_lantern_eye_out_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_flatten_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_flatten_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_flatten_tensor_intt_intt_dimname)
  LOAD_SYMBOL(_lantern_Tensor_flatten_tensor_intt_intt_dimname)
  LOAD_SYMBOL(_lantern_flatten_tensor_dimname_dimname_dimname)
  LOAD_SYMBOL(_lantern_Tensor_flatten_tensor_dimname_dimname_dimname)
  LOAD_SYMBOL(_lantern_flatten_tensor_dimnamelist_dimname)
  LOAD_SYMBOL(_lantern_Tensor_flatten_tensor_dimnamelist_dimname)
  LOAD_SYMBOL(_lantern_fill__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_fill__tensor_scalar)
  LOAD_SYMBOL(_lantern_fill__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_fill__tensor_tensor)
  LOAD_SYMBOL(_lantern_floor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_floor_tensor)
  LOAD_SYMBOL(_lantern_floor__tensor)
  LOAD_SYMBOL(_lantern_Tensor_floor__tensor)
  LOAD_SYMBOL(_lantern_floor_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_floor_divide_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_floor_divide_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_floor_divide__tensor_tensor)
  LOAD_SYMBOL(_lantern_floor_divide_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_floor_divide_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_floor_divide_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_floor_divide__tensor_scalar)
  LOAD_SYMBOL(_lantern_frac_tensor)
  LOAD_SYMBOL(_lantern_Tensor_frac_tensor)
  LOAD_SYMBOL(_lantern_frac__tensor)
  LOAD_SYMBOL(_lantern_Tensor_frac__tensor)
  LOAD_SYMBOL(_lantern_frac_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_full_intarrayref_scalar_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_full_intarrayref_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_full_out_tensor_intarrayref_scalar)
  LOAD_SYMBOL(_lantern_full_like_tensor_scalar_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_from_file_stdstring_bool_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_grid_sampler_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_grid_sampler_2d_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_grid_sampler_2d_backward_tensor_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_grid_sampler_3d_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_grid_sampler_3d_backward_tensor_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_hann_window_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_hann_window_intt_bool_tensoroptions)
  LOAD_SYMBOL(_lantern_hamming_window_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_hamming_window_intt_bool_tensoroptions)
  LOAD_SYMBOL(_lantern_hamming_window_intt_bool_double_tensoroptions)
  LOAD_SYMBOL(_lantern_hamming_window_intt_bool_double_double_tensoroptions)
  LOAD_SYMBOL(_lantern_hinge_embedding_loss_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern_ger_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ger_tensor_tensor)
  LOAD_SYMBOL(_lantern_ger_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_group_norm_tensor_intt_tensor_tensor_double_bool)
  LOAD_SYMBOL(_lantern_fft_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_fft_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_ifft_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_ifft_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_rfft_tensor_intt_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_rfft_tensor_intt_bool_bool)
  LOAD_SYMBOL(_lantern_irfft_tensor_intt_bool_bool_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_irfft_tensor_intt_bool_bool_intarrayref)
  LOAD_SYMBOL(_lantern__fft_with_size_tensor_intt_bool_bool_bool_intarrayref_bool_bool_intarrayref)
  LOAD_SYMBOL(_lantern__cufft_get_plan_cache_size_intt)
  LOAD_SYMBOL(_lantern__cufft_get_plan_cache_max_size_intt)
  LOAD_SYMBOL(_lantern__cufft_set_plan_cache_max_size_intt_intt)
  LOAD_SYMBOL(_lantern__cufft_clear_plan_cache_intt)
  LOAD_SYMBOL(_lantern_index_tensor_tensorlist)
  LOAD_SYMBOL(_lantern_Tensor_index_tensor_tensorlist)
  LOAD_SYMBOL(_lantern_Tensor_index_copy__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_copy_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_copy_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_copy__tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_copy_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_copy_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_put__tensor_tensorlist_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_index_put__tensor_tensorlist_tensor_bool)
  LOAD_SYMBOL(_lantern_index_put_tensor_tensorlist_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_index_put_tensor_tensorlist_tensor_bool)
  LOAD_SYMBOL(_lantern__index_put_impl__tensor_tensorlist_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_instance_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double_bool)
  LOAD_SYMBOL(_lantern_inverse_tensor)
  LOAD_SYMBOL(_lantern_Tensor_inverse_tensor)
  LOAD_SYMBOL(_lantern_inverse_out_tensor_tensor)
  LOAD_SYMBOL(_lantern__inverse_helper_tensor)
  LOAD_SYMBOL(_lantern_isclose_tensor_tensor_double_double_bool)
  LOAD_SYMBOL(_lantern_Tensor_isclose_tensor_tensor_double_double_bool)
  LOAD_SYMBOL(_lantern_isnan_tensor)
  LOAD_SYMBOL(_lantern_is_distributed_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_distributed_tensor)
  LOAD_SYMBOL(_lantern_is_floating_point_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_floating_point_tensor)
  LOAD_SYMBOL(_lantern_is_complex_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_complex_tensor)
  LOAD_SYMBOL(_lantern_is_nonzero_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_nonzero_tensor)
  LOAD_SYMBOL(_lantern_is_same_size_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_same_size_tensor_tensor)
  LOAD_SYMBOL(_lantern_is_signed_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_signed_tensor)
  LOAD_SYMBOL(_lantern_kl_div_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_kl_div_backward_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_kthvalue_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_kthvalue_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_kthvalue_out_tensor_tensor_tensor_intt_intt_bool)
  LOAD_SYMBOL(_lantern_kthvalue_tensor_intt_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_kthvalue_tensor_intt_dimname_bool)
  LOAD_SYMBOL(_lantern_kthvalue_out_tensor_tensor_tensor_intt_dimname_bool)
  LOAD_SYMBOL(_lantern_layer_norm_tensor_intarrayref_tensor_tensor_double_bool)
  LOAD_SYMBOL(_lantern_native_layer_norm_tensor_tensor_tensor_intt_intt_double)
  LOAD_SYMBOL(_lantern_native_layer_norm_backward_tensor_tensor_tensor_tensor_tensor_intt_intt_stdarraybool)
  LOAD_SYMBOL(_lantern_linear_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_mkldnn_linear_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_linear_int8_weight_fp32_activation_tensor_tensor_tensor_tensor_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_linear_int8_weight_tensor_tensor_tensor_tensor_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_linear_quantize_weight_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_pack_gemm_matrix_fp16_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_linear_fp16_weight_fp32_activation_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_linear_fp16_weight_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_pack_quantized_matrix_tensor)
  LOAD_SYMBOL(_lantern_fbgemm_pack_quantized_matrix_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_linspace_scalar_scalar_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_linspace_out_tensor_scalar_scalar_intt)
  LOAD_SYMBOL(_lantern_log_tensor)
  LOAD_SYMBOL(_lantern_Tensor_log_tensor)
  LOAD_SYMBOL(_lantern_log__tensor)
  LOAD_SYMBOL(_lantern_Tensor_log__tensor)
  LOAD_SYMBOL(_lantern_log_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_log10_tensor)
  LOAD_SYMBOL(_lantern_Tensor_log10_tensor)
  LOAD_SYMBOL(_lantern_log10__tensor)
  LOAD_SYMBOL(_lantern_Tensor_log10__tensor)
  LOAD_SYMBOL(_lantern_log10_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_log1p_tensor)
  LOAD_SYMBOL(_lantern_Tensor_log1p_tensor)
  LOAD_SYMBOL(_lantern_log1p__tensor)
  LOAD_SYMBOL(_lantern_Tensor_log1p__tensor)
  LOAD_SYMBOL(_lantern_log1p_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_log2_tensor)
  LOAD_SYMBOL(_lantern_Tensor_log2_tensor)
  LOAD_SYMBOL(_lantern_log2__tensor)
  LOAD_SYMBOL(_lantern_Tensor_log2__tensor)
  LOAD_SYMBOL(_lantern_log2_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_logdet_tensor)
  LOAD_SYMBOL(_lantern_Tensor_logdet_tensor)
  LOAD_SYMBOL(_lantern_logspace_scalar_scalar_intt_double_tensoroptions)
  LOAD_SYMBOL(_lantern_logspace_out_tensor_scalar_scalar_intt_double)
  LOAD_SYMBOL(_lantern_log_softmax_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_log_softmax_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_log_softmax_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_log_softmax_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern__log_softmax_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__log_softmax_backward_data_tensor_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_logsumexp_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_Tensor_logsumexp_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_logsumexp_out_tensor_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_logsumexp_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_Tensor_logsumexp_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_logsumexp_out_tensor_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_margin_ranking_loss_tensor_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern_matmul_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_matmul_tensor_tensor)
  LOAD_SYMBOL(_lantern_matmul_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_matrix_rank_tensor_double_bool)
  LOAD_SYMBOL(_lantern_matrix_rank_tensor_bool)
  LOAD_SYMBOL(_lantern_matrix_power_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_matrix_power_tensor_intt)
  LOAD_SYMBOL(_lantern_max_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_max_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_max_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_max_values_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_Tensor_max_values_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_max_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_max_out_tensor_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_max_values_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_Tensor_max_values_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_max_pool1d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool1d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_mkldnn_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_quantized_max_pool2d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool3d_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_mean_tensor_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_mean_tensor_scalartype)
  LOAD_SYMBOL(_lantern_mean_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_mean_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_mean_out_tensor_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_mean_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_mean_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_mean_out_tensor_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_median_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_median_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_median_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_median_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_median_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_median_out_tensor_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_min_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_min_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_min_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_min_values_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_Tensor_min_values_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_min_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_min_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_min_out_tensor_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_min_values_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_Tensor_min_values_tensor_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_mkldnn_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_mkldnn_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool)
  LOAD_SYMBOL(_lantern_mkldnn_convolution_backward_weights_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool)
  LOAD_SYMBOL(_lantern_mkldnn_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_stdarraybool)
  LOAD_SYMBOL(_lantern_miopen_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)
  LOAD_SYMBOL(_lantern_miopen_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_double)
  LOAD_SYMBOL(_lantern_miopen_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_miopen_convolution_backward_bias_tensor)
  LOAD_SYMBOL(_lantern_miopen_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_convolution_transpose_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_convolution_transpose_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_miopen_convolution_transpose_backward_input_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_convolution_transpose_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_depthwise_convolution_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_depthwise_convolution_backward_input_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_depthwise_convolution_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool_stdarraybool)
  LOAD_SYMBOL(_lantern_miopen_depthwise_convolution_backward_weight_intarrayref_tensor_tensor_intarrayref_intarrayref_intarrayref_intt_bool_bool)
  LOAD_SYMBOL(_lantern_miopen_rnn_tensor_tensorlist_intt_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_miopen_rnn_backward_tensor_tensorlist_intt_tensor_tensor_tensor_tensor_tensor_tensor_tensor_intt_intt_intt_bool_double_bool_bool_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern_mm_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_mm_tensor_tensor)
  LOAD_SYMBOL(_lantern_mm_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__sparse_mm_tensor_tensor)
  LOAD_SYMBOL(_lantern_mode_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_mode_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_mode_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_mode_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_mode_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_mode_out_tensor_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_mul_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_mul_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_mul__tensor_tensor)
  LOAD_SYMBOL(_lantern_mul_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_mul_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_mul_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_mul__tensor_scalar)
  LOAD_SYMBOL(_lantern_mv_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_mv_tensor_tensor)
  LOAD_SYMBOL(_lantern_mv_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_mvlgamma_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_mvlgamma_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_mvlgamma__tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_narrow_copy_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_narrow_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_narrow_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_narrow_tensor_intt_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_narrow_tensor_intt_tensor_intt)
  LOAD_SYMBOL(_lantern_native_batch_norm_tensor_tensor_tensor_tensor_tensor_bool_double_double)
  LOAD_SYMBOL(_lantern_native_batch_norm_out_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_double)
  LOAD_SYMBOL(_lantern_batch_norm_stats_tensor_double)
  LOAD_SYMBOL(_lantern_batch_norm_elemt_tensor_tensor_tensor_tensor_tensor_double)
  LOAD_SYMBOL(_lantern_batch_norm_elemt_out_tensor_tensor_tensor_tensor_tensor_tensor_double)
  LOAD_SYMBOL(_lantern_batch_norm_gather_stats_tensor_tensor_tensor_tensor_tensor_double_double_intt)
  LOAD_SYMBOL(_lantern_batch_norm_gather_stats_with_counts_tensor_tensor_tensor_tensor_tensor_double_double_intarrayref)
  LOAD_SYMBOL(_lantern_native_batch_norm_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_bool_double_stdarraybool)
  LOAD_SYMBOL(_lantern_batch_norm_backward_reduce_tensor_tensor_tensor_tensor_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern_batch_norm_backward_elemt_tensor_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_batch_norm_update_stats_tensor_tensor_tensor_double)
  LOAD_SYMBOL(_lantern__nnpack_available)
  LOAD_SYMBOL(_lantern__nnpack_spatial_convolution_tensor_tensor_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern__nnpack_spatial_convolution_backward_tensor_tensor_tensor_intarrayref_stdarraybool)
  LOAD_SYMBOL(_lantern__nnpack_spatial_convolution_backward_input_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern__nnpack_spatial_convolution_backward_weight_tensor_intarrayref_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_ones_intarrayref_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_ones_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_ones_out_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_ones_like_tensor_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_pairwise_distance_tensor_tensor_double_double_bool)
  LOAD_SYMBOL(_lantern_cdist_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern__cdist_forward_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern__cdist_backward_tensor_tensor_tensor_double_tensor)
  LOAD_SYMBOL(_lantern_pdist_tensor_double)
  LOAD_SYMBOL(_lantern__pdist_forward_tensor_double)
  LOAD_SYMBOL(_lantern__pdist_backward_tensor_tensor_double_tensor)
  LOAD_SYMBOL(_lantern_cosine_similarity_tensor_tensor_intt_double)
  LOAD_SYMBOL(_lantern_Tensor_permute_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_numpy_t_tensor)
  LOAD_SYMBOL(_lantern_pixel_shuffle_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_is_pinned_tensor)
  LOAD_SYMBOL(_lantern_Tensor_pin_memory_tensor)
  LOAD_SYMBOL(_lantern_pinverse_tensor_double)
  LOAD_SYMBOL(_lantern_Tensor_pinverse_tensor_double)
  LOAD_SYMBOL(_lantern_poisson_nll_loss_tensor_tensor_bool_bool_double_intt)
  LOAD_SYMBOL(_lantern_scalar_tensor_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_rand_intarrayref_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_rand_intarrayref_generator_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_rand_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_rand_intarrayref_generator_tensoroptions)
  LOAD_SYMBOL(_lantern_rand_out_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_rand_out_tensor_intarrayref_generator)
  LOAD_SYMBOL(_lantern_rand_like_tensor_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_randint_intt_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_randint_intt_intarrayref_generator_tensoroptions)
  LOAD_SYMBOL(_lantern_randint_intt_intt_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_randint_intt_intt_intarrayref_generator_tensoroptions)
  LOAD_SYMBOL(_lantern_randint_out_tensor_intt_intarrayref)
  LOAD_SYMBOL(_lantern_randint_out_tensor_intt_intarrayref_generator)
  LOAD_SYMBOL(_lantern_randint_out_tensor_intt_intt_intarrayref)
  LOAD_SYMBOL(_lantern_randint_out_tensor_intt_intt_intarrayref_generator)
  LOAD_SYMBOL(_lantern_randint_like_tensor_intt_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_randint_like_tensor_intt_intt_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_randn_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_randn_intarrayref_generator_tensoroptions)
  LOAD_SYMBOL(_lantern_randn_intarrayref_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_randn_intarrayref_generator_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_randn_out_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_randn_out_tensor_intarrayref_generator)
  LOAD_SYMBOL(_lantern_randn_like_tensor_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern_randperm_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_randperm_intt_generator_tensoroptions)
  LOAD_SYMBOL(_lantern_randperm_out_tensor_intt)
  LOAD_SYMBOL(_lantern_randperm_out_tensor_intt_generator)
  LOAD_SYMBOL(_lantern_range_scalar_scalar_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_range_scalar_scalar_tensoroptions)
  LOAD_SYMBOL(_lantern_range_out_tensor_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_reciprocal_tensor)
  LOAD_SYMBOL(_lantern_Tensor_reciprocal_tensor)
  LOAD_SYMBOL(_lantern_reciprocal__tensor)
  LOAD_SYMBOL(_lantern_Tensor_reciprocal__tensor)
  LOAD_SYMBOL(_lantern_reciprocal_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_neg_tensor)
  LOAD_SYMBOL(_lantern_Tensor_neg_tensor)
  LOAD_SYMBOL(_lantern_neg__tensor)
  LOAD_SYMBOL(_lantern_Tensor_neg__tensor)
  LOAD_SYMBOL(_lantern_neg_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_repeat_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_repeat_interleave_tensor)
  LOAD_SYMBOL(_lantern_repeat_interleave_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_repeat_interleave_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_repeat_interleave_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_repeat_interleave_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_reshape_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_reshape_tensor_intarrayref)
  LOAD_SYMBOL(_lantern__mkldnn_reshape_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_reshape_as_tensor_tensor)
  LOAD_SYMBOL(_lantern_round_tensor)
  LOAD_SYMBOL(_lantern_Tensor_round_tensor)
  LOAD_SYMBOL(_lantern_round__tensor)
  LOAD_SYMBOL(_lantern_Tensor_round__tensor)
  LOAD_SYMBOL(_lantern_round_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_rrelu_tensor_scalar_scalar_bool_generator)
  LOAD_SYMBOL(_lantern_rrelu__tensor_scalar_scalar_bool_generator)
  LOAD_SYMBOL(_lantern_relu_tensor)
  LOAD_SYMBOL(_lantern_Tensor_relu_tensor)
  LOAD_SYMBOL(_lantern_relu__tensor)
  LOAD_SYMBOL(_lantern_Tensor_relu__tensor)
  LOAD_SYMBOL(_lantern_prelu_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_prelu_tensor_tensor)
  LOAD_SYMBOL(_lantern_prelu_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_prelu_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_gelu_tensor)
  LOAD_SYMBOL(_lantern_gelu_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_hardshrink_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_hardshrink_tensor_scalar)
  LOAD_SYMBOL(_lantern_hardshrink_backward_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_hardshrink_backward_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_rsqrt_tensor)
  LOAD_SYMBOL(_lantern_Tensor_rsqrt_tensor)
  LOAD_SYMBOL(_lantern_rsqrt__tensor)
  LOAD_SYMBOL(_lantern_Tensor_rsqrt__tensor)
  LOAD_SYMBOL(_lantern_rsqrt_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_select_tensor_dimname_intt)
  LOAD_SYMBOL(_lantern_Tensor_select_tensor_dimname_intt)
  LOAD_SYMBOL(_lantern_select_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_select_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_selu_tensor)
  LOAD_SYMBOL(_lantern_selu__tensor)
  LOAD_SYMBOL(_lantern_celu_tensor_scalar)
  LOAD_SYMBOL(_lantern_celu__tensor_scalar)
  LOAD_SYMBOL(_lantern_sigmoid_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sigmoid_tensor)
  LOAD_SYMBOL(_lantern_sigmoid__tensor)
  LOAD_SYMBOL(_lantern_Tensor_sigmoid__tensor)
  LOAD_SYMBOL(_lantern_sigmoid_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_sin_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sin_tensor)
  LOAD_SYMBOL(_lantern_sin__tensor)
  LOAD_SYMBOL(_lantern_Tensor_sin__tensor)
  LOAD_SYMBOL(_lantern_sin_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_sinh_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sinh_tensor)
  LOAD_SYMBOL(_lantern_sinh__tensor)
  LOAD_SYMBOL(_lantern_Tensor_sinh__tensor)
  LOAD_SYMBOL(_lantern_sinh_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_detach_tensor)
  LOAD_SYMBOL(_lantern_Tensor_detach_tensor)
  LOAD_SYMBOL(_lantern_detach__tensor)
  LOAD_SYMBOL(_lantern_Tensor_detach__tensor)
  LOAD_SYMBOL(_lantern_size_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_size_tensor_intt)
  LOAD_SYMBOL(_lantern_size_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_size_tensor_dimname)
  LOAD_SYMBOL(_lantern_slice_tensor_intt_intt_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_slice_tensor_intt_intt_intt_intt)
  LOAD_SYMBOL(_lantern_slogdet_tensor)
  LOAD_SYMBOL(_lantern_Tensor_slogdet_tensor)
  LOAD_SYMBOL(_lantern_smm_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_smm_tensor_tensor)
  LOAD_SYMBOL(_lantern_softmax_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_softmax_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_softmax_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_softmax_tensor_dimname_scalartype)
  LOAD_SYMBOL(_lantern__softmax_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__softmax_backward_data_tensor_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_split_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_split_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_split_with_sizes_tensor_intarrayref_intt)
  LOAD_SYMBOL(_lantern_Tensor_split_with_sizes_tensor_intarrayref_intt)
  LOAD_SYMBOL(_lantern_squeeze_tensor)
  LOAD_SYMBOL(_lantern_Tensor_squeeze_tensor)
  LOAD_SYMBOL(_lantern_squeeze_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_squeeze_tensor_intt)
  LOAD_SYMBOL(_lantern_squeeze_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_squeeze_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_squeeze__tensor)
  LOAD_SYMBOL(_lantern_Tensor_squeeze__tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_squeeze__tensor_dimname)
  LOAD_SYMBOL(_lantern_sspaddmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_sspaddmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_sspaddmm_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_stack_tensorlist_intt)
  LOAD_SYMBOL(_lantern_stack_out_tensor_tensorlist_intt)
  LOAD_SYMBOL(_lantern_stft_tensor_intt_intt_intt_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_stft_tensor_intt_intt_intt_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_stride_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_stride_tensor_intt)
  LOAD_SYMBOL(_lantern_stride_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_stride_tensor_dimname)
  LOAD_SYMBOL(_lantern_sum_tensor_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_sum_tensor_scalartype)
  LOAD_SYMBOL(_lantern_sum_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_sum_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_sum_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_sum_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_sum_out_tensor_tensor_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_sum_out_tensor_tensor_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_sum_to_size_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_sqrt_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sqrt_tensor)
  LOAD_SYMBOL(_lantern_sqrt__tensor)
  LOAD_SYMBOL(_lantern_Tensor_sqrt__tensor)
  LOAD_SYMBOL(_lantern_sqrt_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_square_tensor)
  LOAD_SYMBOL(_lantern_Tensor_square_tensor)
  LOAD_SYMBOL(_lantern_square__tensor)
  LOAD_SYMBOL(_lantern_Tensor_square__tensor)
  LOAD_SYMBOL(_lantern_std_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_std_tensor_bool)
  LOAD_SYMBOL(_lantern_std_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_std_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_std_mean_tensor_bool)
  LOAD_SYMBOL(_lantern_std_mean_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_std_mean_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_std_out_tensor_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_std_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_std_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_std_out_tensor_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_prod_tensor_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_prod_tensor_scalartype)
  LOAD_SYMBOL(_lantern_prod_tensor_intt_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_prod_tensor_intt_bool_scalartype)
  LOAD_SYMBOL(_lantern_prod_out_tensor_tensor_intt_bool_scalartype)
  LOAD_SYMBOL(_lantern_prod_tensor_dimname_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_prod_tensor_dimname_bool_scalartype)
  LOAD_SYMBOL(_lantern_prod_out_tensor_tensor_dimname_bool_scalartype)
  LOAD_SYMBOL(_lantern_t_tensor)
  LOAD_SYMBOL(_lantern_Tensor_t_tensor)
  LOAD_SYMBOL(_lantern_Tensor_t__tensor)
  LOAD_SYMBOL(_lantern_tan_tensor)
  LOAD_SYMBOL(_lantern_Tensor_tan_tensor)
  LOAD_SYMBOL(_lantern_tan__tensor)
  LOAD_SYMBOL(_lantern_Tensor_tan__tensor)
  LOAD_SYMBOL(_lantern_tan_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_tanh_tensor)
  LOAD_SYMBOL(_lantern_Tensor_tanh_tensor)
  LOAD_SYMBOL(_lantern_tanh__tensor)
  LOAD_SYMBOL(_lantern_Tensor_tanh__tensor)
  LOAD_SYMBOL(_lantern_tanh_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_tensordot_tensor_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_threshold_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_threshold__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_threshold_out_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_threshold_backward_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_transpose_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_transpose_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_transpose_tensor_dimname_dimname)
  LOAD_SYMBOL(_lantern_Tensor_transpose_tensor_dimname_dimname)
  LOAD_SYMBOL(_lantern__mkldnn_transpose_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_transpose__tensor_intt_intt)
  LOAD_SYMBOL(_lantern__mkldnn_transpose__tensor_intt_intt)
  LOAD_SYMBOL(_lantern_one_hot_tensor_intt)
  LOAD_SYMBOL(_lantern_flip_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_flip_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_roll_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_roll_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_rot90_tensor_intt_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_rot90_tensor_intt_intarrayref)
  LOAD_SYMBOL(_lantern_trapz_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_trapz_tensor_double_intt)
  LOAD_SYMBOL(_lantern__trilinear_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_triplet_margin_loss_tensor_tensor_tensor_double_double_double_bool_intt)
  LOAD_SYMBOL(_lantern_true_divide_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_true_divide_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_true_divide__tensor_tensor)
  LOAD_SYMBOL(_lantern_true_divide_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_true_divide_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_true_divide_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_true_divide__tensor_scalar)
  LOAD_SYMBOL(_lantern_trunc_tensor)
  LOAD_SYMBOL(_lantern_Tensor_trunc_tensor)
  LOAD_SYMBOL(_lantern_trunc__tensor)
  LOAD_SYMBOL(_lantern_Tensor_trunc__tensor)
  LOAD_SYMBOL(_lantern_trunc_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_type_as_tensor_tensor)
  LOAD_SYMBOL(_lantern__has_compatible_shallow_copy_type_tensor_tensor)
  LOAD_SYMBOL(_lantern__unique_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_unique_dim_tensor_intt_bool_bool_bool)
  LOAD_SYMBOL(_lantern_unique_consecutive_tensor_bool_bool_intt)
  LOAD_SYMBOL(_lantern_unique_dim_consecutive_tensor_intt_bool_bool)
  LOAD_SYMBOL(_lantern__unique2_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern__unsafe_view_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_unsqueeze_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_unsqueeze_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_unsqueeze__tensor_intt)
  LOAD_SYMBOL(_lantern_var_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_var_tensor_bool)
  LOAD_SYMBOL(_lantern_var_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_var_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_var_out_tensor_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_var_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_var_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_var_out_tensor_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_var_mean_tensor_bool)
  LOAD_SYMBOL(_lantern_var_mean_tensor_intarrayref_bool_bool)
  LOAD_SYMBOL(_lantern_var_mean_tensor_dimnamelist_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_view_as_tensor_tensor)
  LOAD_SYMBOL(_lantern_where_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_where_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_where_tensor)
  LOAD_SYMBOL(_lantern__s_where_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_norm_except_dim_tensor_intt_intt)
  LOAD_SYMBOL(_lantern__weight_norm_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__weight_norm_cuda_interface_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__weight_norm_cuda_interface_backward_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__weight_norm_differentiable_backward_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_zeros_intarrayref_dimnamelist_tensoroptions)
  LOAD_SYMBOL(_lantern_zeros_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_zeros_out_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_zeros_like_tensor_tensoroptions_memoryformat)
  LOAD_SYMBOL(_lantern__standard_gamma_grad_tensor_tensor)
  LOAD_SYMBOL(_lantern__standard_gamma_tensor_generator)
  LOAD_SYMBOL(_lantern__dirichlet_grad_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__sample_dirichlet_tensor_generator)
  LOAD_SYMBOL(_lantern_poisson_tensor_generator)
  LOAD_SYMBOL(_lantern_native_norm_tensor_scalar)
  LOAD_SYMBOL(_lantern__sparse_sum_tensor)
  LOAD_SYMBOL(_lantern__sparse_sum_tensor_scalartype)
  LOAD_SYMBOL(_lantern__sparse_sum_tensor_intarrayref)
  LOAD_SYMBOL(_lantern__sparse_sum_tensor_intarrayref_scalartype)
  LOAD_SYMBOL(_lantern__sparse_sum_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar_scalartype)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar_intarrayref_bool)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar_intarrayref_bool)
  LOAD_SYMBOL(_lantern_norm_out_tensor_tensor_scalar_intarrayref_bool_scalartype)
  LOAD_SYMBOL(_lantern_norm_out_tensor_tensor_scalar_intarrayref_bool)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_norm_tensor_scalar_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_Tensor_norm_tensor_scalar_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool_scalartype)
  LOAD_SYMBOL(_lantern_norm_out_tensor_tensor_scalar_dimnamelist_bool)
  LOAD_SYMBOL(_lantern_frobenius_norm_tensor)
  LOAD_SYMBOL(_lantern_frobenius_norm_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_frobenius_norm_out_tensor_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_nuclear_norm_tensor_bool)
  LOAD_SYMBOL(_lantern_nuclear_norm_out_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_nuclear_norm_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_nuclear_norm_out_tensor_tensor_intarrayref_bool)
  LOAD_SYMBOL(_lantern_clone_tensor_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_clone_tensor_memoryformat)
  LOAD_SYMBOL(_lantern_resize_as__tensor_tensor_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_resize_as__tensor_tensor_memoryformat)
  LOAD_SYMBOL(_lantern_pow_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_pow_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_pow_tensor_scalar)
  LOAD_SYMBOL(_lantern_zero__tensor)
  LOAD_SYMBOL(_lantern_Tensor_zero__tensor)
  LOAD_SYMBOL(_lantern_sub_out_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_sub_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_sub_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_sub__tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_sub_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_sub_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_sub__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_rsub_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_rsub_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern__sparse_addmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addmm_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addmm__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_sparse_coo_tensor_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern_sparse_coo_tensor_tensor_tensor_tensoroptions)
  LOAD_SYMBOL(_lantern_sparse_coo_tensor_tensor_tensor_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern__sparse_coo_tensor_unsafe_tensor_tensor_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern__sparse_coo_tensor_with_dims_intt_intt_intarrayref_tensoroptions)
  LOAD_SYMBOL(_lantern__sparse_coo_tensor_with_dims_and_tensors_intt_intt_intarrayref_tensor_tensor_tensoroptions)
  LOAD_SYMBOL(_lantern_Tensor_sparse_resize__tensor_intarrayref_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_sparse_resize_and_clear__tensor_intarrayref_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_sparse_mask_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_to_dense_tensor)
  LOAD_SYMBOL(_lantern_to_dense_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sparse_dim_tensor)
  LOAD_SYMBOL(_lantern_Tensor__dimi_tensor)
  LOAD_SYMBOL(_lantern_Tensor_dense_dim_tensor)
  LOAD_SYMBOL(_lantern_Tensor__dimv_tensor)
  LOAD_SYMBOL(_lantern_Tensor__nnz_tensor)
  LOAD_SYMBOL(_lantern_Tensor_coalesce_tensor)
  LOAD_SYMBOL(_lantern_Tensor_is_coalesced_tensor)
  LOAD_SYMBOL(_lantern_Tensor__indices_tensor)
  LOAD_SYMBOL(_lantern_Tensor__values_tensor)
  LOAD_SYMBOL(_lantern_Tensor__coalesced__tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_indices_tensor)
  LOAD_SYMBOL(_lantern_Tensor_values_tensor)
  LOAD_SYMBOL(_lantern_hspmm_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_hspmm_tensor_tensor)
  LOAD_SYMBOL(_lantern_copy_sparse_to_sparse__tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_unbind_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_unbind_tensor_intt)
  LOAD_SYMBOL(_lantern_unbind_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_unbind_tensor_dimname)
  LOAD_SYMBOL(_lantern_Tensor_to_sparse_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_to_sparse_tensor)
  LOAD_SYMBOL(_lantern_Tensor_to_mkldnn_tensor)
  LOAD_SYMBOL(_lantern_mkldnn_reorder_conv2d_weight_tensor_intarrayref_intarrayref_intarrayref_intt)
  LOAD_SYMBOL(_lantern_to_mkldnn_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_quantize_per_tensor_tensor_double_intt_scalartype)
  LOAD_SYMBOL(_lantern_quantize_per_channel_tensor_tensor_tensor_intt_scalartype)
  LOAD_SYMBOL(_lantern_dequantize_tensor)
  LOAD_SYMBOL(_lantern_Tensor_dequantize_tensor)
  LOAD_SYMBOL(_lantern_q_scale_tensor)
  LOAD_SYMBOL(_lantern_Tensor_q_scale_tensor)
  LOAD_SYMBOL(_lantern_q_zero_point_tensor)
  LOAD_SYMBOL(_lantern_Tensor_q_zero_point_tensor)
  LOAD_SYMBOL(_lantern_q_per_channel_scales_tensor)
  LOAD_SYMBOL(_lantern_Tensor_q_per_channel_scales_tensor)
  LOAD_SYMBOL(_lantern_q_per_channel_zero_points_tensor)
  LOAD_SYMBOL(_lantern_Tensor_q_per_channel_zero_points_tensor)
  LOAD_SYMBOL(_lantern_q_per_channel_axis_tensor)
  LOAD_SYMBOL(_lantern_Tensor_q_per_channel_axis_tensor)
  LOAD_SYMBOL(_lantern_int_repr_tensor)
  LOAD_SYMBOL(_lantern_Tensor_int_repr_tensor)
  LOAD_SYMBOL(_lantern__make_per_tensor_quantized_tensor_tensor_double_intt)
  LOAD_SYMBOL(_lantern__make_per_channel_quantized_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_qscheme_tensor)
  LOAD_SYMBOL(_lantern_fake_quantize_per_tensor_affine_tensor_double_intt_intt_intt)
  LOAD_SYMBOL(_lantern_fake_quantize_per_tensor_affine_backward_tensor_tensor_double_intt_intt_intt)
  LOAD_SYMBOL(_lantern_fake_quantize_per_channel_affine_tensor_tensor_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_fake_quantize_per_channel_affine_backward_tensor_tensor_tensor_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_Tensor_to_tensor_tensoroptions_bool_bool_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_to_tensor_device_scalartype_bool_bool_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_to_tensor_scalartype_bool_bool_memoryformat)
  LOAD_SYMBOL(_lantern_Tensor_to_tensor_tensor_bool_bool_memoryformat)
  LOAD_SYMBOL(_lantern_meshgrid_tensorlist)
  LOAD_SYMBOL(_lantern_cartesian_prod_tensorlist)
  LOAD_SYMBOL(_lantern_combinations_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_item_tensor)
  LOAD_SYMBOL(_lantern_result_type_tensor_tensor)
  LOAD_SYMBOL(_lantern_result_type_tensor_scalar)
  LOAD_SYMBOL(_lantern_result_type_scalar_tensor)
  LOAD_SYMBOL(_lantern_result_type_scalar_scalar)
  LOAD_SYMBOL(_lantern_can_cast_scalartype_scalartype)
  LOAD_SYMBOL(_lantern_promote_types_scalartype_scalartype)
  LOAD_SYMBOL(_lantern__local_scalar_dense_tensor)
  LOAD_SYMBOL(_lantern__thnn_fused_lstm_cell_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__thnn_fused_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern__thnn_differentiable_lstm_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__thnn_fused_gru_cell_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__thnn_fused_gru_cell_backward_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern__thnn_differentiable_gru_cell_backward_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool)
  LOAD_SYMBOL(_lantern_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool)
  LOAD_SYMBOL(_lantern_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)
  LOAD_SYMBOL(_lantern_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)
  LOAD_SYMBOL(_lantern_rnn_tanh_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)
  LOAD_SYMBOL(_lantern_rnn_tanh_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)
  LOAD_SYMBOL(_lantern_rnn_relu_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)
  LOAD_SYMBOL(_lantern_rnn_relu_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)
  LOAD_SYMBOL(_lantern_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_quantized_lstm_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_bool_scalartype_bool)
  LOAD_SYMBOL(_lantern_quantized_lstm_tensor_tensor_tensorlist_tensorlist_bool_intt_double_bool_bool_scalartype_bool)
  LOAD_SYMBOL(_lantern_quantized_gru_tensor_tensor_tensorlist_bool_intt_double_bool_bool_bool)
  LOAD_SYMBOL(_lantern_quantized_gru_tensor_tensor_tensor_tensorlist_bool_intt_double_bool_bool)
  LOAD_SYMBOL(_lantern_quantized_lstm_cell_tensor_tensorlist_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_quantized_gru_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_quantized_rnn_relu_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_quantized_rnn_tanh_cell_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_tensor_scalar_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern__pack_padded_sequence_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern__pack_padded_sequence_backward_tensor_intarrayref_tensor_bool)
  LOAD_SYMBOL(_lantern__pad_packed_sequence_tensor_tensor_bool_scalar_intt)
  LOAD_SYMBOL(_lantern_Tensor_set__tensor_storage)
  LOAD_SYMBOL(_lantern_Tensor_set__tensor_storage_intt_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_set__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_set__tensor)
  LOAD_SYMBOL(_lantern_Tensor_set_quantizer__tensor_constquantizerptr)
  LOAD_SYMBOL(_lantern_Tensor_is_set_to_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_masked_fill__tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_masked_fill_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_masked_fill_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_masked_fill__tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_masked_fill_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_masked_fill_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_masked_scatter__tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_masked_scatter_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_masked_scatter_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_view_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_Tensor_put__tensor_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_index_add__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_add_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_add_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_add_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_add_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_fill__tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_index_fill_tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_index_fill_tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_index_fill__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_fill_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_fill_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_fill__tensor_dimname_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_index_fill__tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_fill_tensor_dimname_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_index_fill_tensor_dimname_tensor_scalar)
  LOAD_SYMBOL(_lantern_index_fill_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_fill_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_scatter_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter__tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_scatter_tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_scatter_tensor_intt_tensor_scalar)
  LOAD_SYMBOL(_lantern_scatter_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_scatter_tensor_dimname_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_scatter_tensor_dimname_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_scatter_add__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_scatter_add_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter_add_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_scatter_add_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_scatter_add_tensor_dimname_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lt__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_lt__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_gt__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_gt__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_le__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_le__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ge__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_ge__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_eq__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_eq__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ne__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_ne__tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_and_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_and_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_and_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_and_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_and_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_and_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_and__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_and__tensor_tensor)
  LOAD_SYMBOL(_lantern___and___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___and___tensor_scalar)
  LOAD_SYMBOL(_lantern___and___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___and___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___iand___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___iand___tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_or_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_or_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_or_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_or_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_or_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_or_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_or__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_or__tensor_tensor)
  LOAD_SYMBOL(_lantern___or___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___or___tensor_scalar)
  LOAD_SYMBOL(_lantern___or___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___or___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___ior___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___ior___tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_xor_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_bitwise_xor_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_xor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_xor_tensor_scalar)
  LOAD_SYMBOL(_lantern_bitwise_xor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_xor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_xor__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_bitwise_xor__tensor_tensor)
  LOAD_SYMBOL(_lantern___xor___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___xor___tensor_scalar)
  LOAD_SYMBOL(_lantern___xor___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___xor___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___ixor___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___ixor___tensor_tensor)
  LOAD_SYMBOL(_lantern___lshift___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___lshift___tensor_scalar)
  LOAD_SYMBOL(_lantern___lshift___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___lshift___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___ilshift___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___ilshift___tensor_tensor)
  LOAD_SYMBOL(_lantern___rshift___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___rshift___tensor_scalar)
  LOAD_SYMBOL(_lantern___rshift___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___rshift___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor___irshift___tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor___irshift___tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lgamma__tensor)
  LOAD_SYMBOL(_lantern_Tensor_atan2__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_tril__tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_triu__tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_digamma__tensor)
  LOAD_SYMBOL(_lantern_Tensor_polygamma__tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_renorm__tensor_scalar_intt_scalar)
  LOAD_SYMBOL(_lantern_Tensor_pow__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_pow__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lerp__tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_lerp__tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_fmod__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_fmod__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_remainder__tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_remainder__tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_addbmm__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addbmm_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_addbmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addbmm_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addcdiv__tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_random__tensor_intt_intt_generator)
  LOAD_SYMBOL(_lantern_Tensor_random__tensor_intt_generator)
  LOAD_SYMBOL(_lantern_Tensor_random__tensor_generator)
  LOAD_SYMBOL(_lantern_Tensor_uniform__tensor_double_double_generator)
  LOAD_SYMBOL(_lantern_Tensor_cauchy__tensor_double_double_generator)
  LOAD_SYMBOL(_lantern_Tensor_log_normal__tensor_double_double_generator)
  LOAD_SYMBOL(_lantern_Tensor_exponential__tensor_double_generator)
  LOAD_SYMBOL(_lantern_Tensor_geometric__tensor_double_generator)
  LOAD_SYMBOL(_lantern_diag_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_diag_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_diag_tensor_intt)
  LOAD_SYMBOL(_lantern_cross_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_cross_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_cross_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_triu_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_triu_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_triu_tensor_intt)
  LOAD_SYMBOL(_lantern_tril_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_tril_tensor_intt)
  LOAD_SYMBOL(_lantern_Tensor_tril_tensor_intt)
  LOAD_SYMBOL(_lantern_tril_indices_intt_intt_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_triu_indices_intt_intt_intt_tensoroptions)
  LOAD_SYMBOL(_lantern_trace_tensor)
  LOAD_SYMBOL(_lantern_Tensor_trace_tensor)
  LOAD_SYMBOL(_lantern_ne_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_ne_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_ne_tensor_scalar)
  LOAD_SYMBOL(_lantern_ne_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_ne_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ne_tensor_tensor)
  LOAD_SYMBOL(_lantern_eq_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_eq_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_eq_tensor_scalar)
  LOAD_SYMBOL(_lantern_eq_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_eq_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_eq_tensor_tensor)
  LOAD_SYMBOL(_lantern_ge_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_ge_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_ge_tensor_scalar)
  LOAD_SYMBOL(_lantern_ge_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_ge_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_ge_tensor_tensor)
  LOAD_SYMBOL(_lantern_le_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_le_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_le_tensor_scalar)
  LOAD_SYMBOL(_lantern_le_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_le_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_le_tensor_tensor)
  LOAD_SYMBOL(_lantern_gt_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_gt_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_gt_tensor_scalar)
  LOAD_SYMBOL(_lantern_gt_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_gt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_gt_tensor_tensor)
  LOAD_SYMBOL(_lantern_lt_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_lt_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_lt_tensor_scalar)
  LOAD_SYMBOL(_lantern_lt_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_lt_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lt_tensor_tensor)
  LOAD_SYMBOL(_lantern_take_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_take_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_take_tensor_tensor)
  LOAD_SYMBOL(_lantern_index_select_out_tensor_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_index_select_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_select_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_index_select_out_tensor_tensor_dimname_tensor)
  LOAD_SYMBOL(_lantern_index_select_tensor_dimname_tensor)
  LOAD_SYMBOL(_lantern_Tensor_index_select_tensor_dimname_tensor)
  LOAD_SYMBOL(_lantern_masked_select_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_masked_select_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_masked_select_tensor_tensor)
  LOAD_SYMBOL(_lantern_nonzero_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_nonzero_tensor)
  LOAD_SYMBOL(_lantern_Tensor_nonzero_tensor)
  LOAD_SYMBOL(_lantern_nonzero_numpy_tensor)
  LOAD_SYMBOL(_lantern_Tensor_nonzero_numpy_tensor)
  LOAD_SYMBOL(_lantern_gather_out_tensor_tensor_intt_tensor_bool)
  LOAD_SYMBOL(_lantern_gather_tensor_intt_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_gather_tensor_intt_tensor_bool)
  LOAD_SYMBOL(_lantern_gather_out_tensor_tensor_dimname_tensor_bool)
  LOAD_SYMBOL(_lantern_gather_tensor_dimname_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_gather_tensor_dimname_tensor_bool)
  LOAD_SYMBOL(_lantern__gather_sparse_backward_tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern_addcmul_out_tensor_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_addcmul_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addcmul_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addcmul__tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_addcdiv_out_tensor_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_addcdiv_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_addcdiv_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_lstsq_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_lstsq_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lstsq_tensor_tensor)
  LOAD_SYMBOL(_lantern_triangular_solve_out_tensor_tensor_tensor_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern_triangular_solve_tensor_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_triangular_solve_tensor_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern__triangular_solve_helper_tensor_tensor_bool_bool_bool)
  LOAD_SYMBOL(_lantern_symeig_out_tensor_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_symeig_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_symeig_tensor_bool_bool)
  LOAD_SYMBOL(_lantern__symeig_helper_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_eig_out_tensor_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_eig_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_eig_tensor_bool)
  LOAD_SYMBOL(_lantern_svd_out_tensor_tensor_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_svd_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_svd_tensor_bool_bool)
  LOAD_SYMBOL(_lantern__svd_helper_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_cholesky_out_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_cholesky_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_cholesky_tensor_bool)
  LOAD_SYMBOL(_lantern__cholesky_helper_tensor_bool)
  LOAD_SYMBOL(_lantern_cholesky_solve_out_tensor_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_cholesky_solve_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_cholesky_solve_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern__cholesky_solve_helper_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_solve_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_solve_tensor_tensor)
  LOAD_SYMBOL(_lantern_solve_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__solve_helper_tensor_tensor)
  LOAD_SYMBOL(_lantern_cholesky_inverse_out_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_cholesky_inverse_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_cholesky_inverse_tensor_bool)
  LOAD_SYMBOL(_lantern_qr_out_tensor_tensor_tensor_bool)
  LOAD_SYMBOL(_lantern_qr_tensor_bool)
  LOAD_SYMBOL(_lantern_Tensor_qr_tensor_bool)
  LOAD_SYMBOL(_lantern__qr_helper_tensor_bool)
  LOAD_SYMBOL(_lantern_geqrf_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_geqrf_tensor)
  LOAD_SYMBOL(_lantern_Tensor_geqrf_tensor)
  LOAD_SYMBOL(_lantern_orgqr_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_orgqr_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_orgqr_tensor_tensor)
  LOAD_SYMBOL(_lantern_ormqr_out_tensor_tensor_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_ormqr_tensor_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_ormqr_tensor_tensor_tensor_bool_bool)
  LOAD_SYMBOL(_lantern__lu_with_info_tensor_bool_bool)
  LOAD_SYMBOL(_lantern_lu_solve_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_lu_solve_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lu_solve_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__lu_solve_helper_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_multinomial_out_tensor_tensor_intt_bool_generator)
  LOAD_SYMBOL(_lantern_multinomial_tensor_intt_bool_generator)
  LOAD_SYMBOL(_lantern_Tensor_multinomial_tensor_intt_bool_generator)
  LOAD_SYMBOL(_lantern__multinomial_alias_setup_tensor)
  LOAD_SYMBOL(_lantern__multinomial_alias_draw_tensor_tensor_intt_generator)
  LOAD_SYMBOL(_lantern_lgamma_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_lgamma_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lgamma_tensor)
  LOAD_SYMBOL(_lantern_digamma_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_digamma_tensor)
  LOAD_SYMBOL(_lantern_Tensor_digamma_tensor)
  LOAD_SYMBOL(_lantern_polygamma_out_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_erfinv_tensor)
  LOAD_SYMBOL(_lantern_Tensor_erfinv_tensor)
  LOAD_SYMBOL(_lantern_Tensor_erfinv__tensor)
  LOAD_SYMBOL(_lantern_erfinv_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_sign_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sign_tensor)
  LOAD_SYMBOL(_lantern_Tensor_sign__tensor)
  LOAD_SYMBOL(_lantern_sign_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_dist_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_dist_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_atan2_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_atan2_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_atan2_tensor_tensor)
  LOAD_SYMBOL(_lantern_lerp_out_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_lerp_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_lerp_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_lerp_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_lerp_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_lerp_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_histc_out_tensor_tensor_intt_scalar_scalar)
  LOAD_SYMBOL(_lantern_histc_tensor_intt_scalar_scalar)
  LOAD_SYMBOL(_lantern_Tensor_histc_tensor_intt_scalar_scalar)
  LOAD_SYMBOL(_lantern_fmod_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_fmod_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_fmod_tensor_scalar)
  LOAD_SYMBOL(_lantern_fmod_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_fmod_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_fmod_tensor_tensor)
  LOAD_SYMBOL(_lantern_remainder_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_remainder_tensor_scalar)
  LOAD_SYMBOL(_lantern_Tensor_remainder_tensor_scalar)
  LOAD_SYMBOL(_lantern_remainder_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_remainder_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_remainder_tensor_tensor)
  LOAD_SYMBOL(_lantern_min_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_min_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_min_tensor_tensor)
  LOAD_SYMBOL(_lantern_min_tensor)
  LOAD_SYMBOL(_lantern_Tensor_min_tensor)
  LOAD_SYMBOL(_lantern_max_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_max_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_max_tensor_tensor)
  LOAD_SYMBOL(_lantern_max_tensor)
  LOAD_SYMBOL(_lantern_Tensor_max_tensor)
  LOAD_SYMBOL(_lantern_median_tensor)
  LOAD_SYMBOL(_lantern_Tensor_median_tensor)
  LOAD_SYMBOL(_lantern_sort_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_sort_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_sort_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_sort_out_tensor_tensor_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_sort_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_sort_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_argsort_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_Tensor_argsort_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_argsort_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_Tensor_argsort_tensor_dimname_bool)
  LOAD_SYMBOL(_lantern_topk_out_tensor_tensor_tensor_intt_intt_bool_bool)
  LOAD_SYMBOL(_lantern_topk_tensor_intt_intt_bool_bool)
  LOAD_SYMBOL(_lantern_Tensor_topk_tensor_intt_intt_bool_bool)
  LOAD_SYMBOL(_lantern_all_tensor)
  LOAD_SYMBOL(_lantern_Tensor_all_tensor)
  LOAD_SYMBOL(_lantern_any_tensor)
  LOAD_SYMBOL(_lantern_Tensor_any_tensor)
  LOAD_SYMBOL(_lantern_renorm_out_tensor_tensor_scalar_intt_scalar)
  LOAD_SYMBOL(_lantern_renorm_tensor_scalar_intt_scalar)
  LOAD_SYMBOL(_lantern_Tensor_renorm_tensor_scalar_intt_scalar)
  LOAD_SYMBOL(_lantern_Tensor_unfold_tensor_intt_intt_intt)
  LOAD_SYMBOL(_lantern_equal_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_equal_tensor_tensor)
  LOAD_SYMBOL(_lantern_pow_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_pow_tensor_tensor)
  LOAD_SYMBOL(_lantern_Tensor_pow_tensor_tensor)
  LOAD_SYMBOL(_lantern_pow_out_tensor_scalar_tensor)
  LOAD_SYMBOL(_lantern_pow_scalar_tensor)
  LOAD_SYMBOL(_lantern_Tensor_normal__tensor_double_double_generator)
  LOAD_SYMBOL(_lantern_normal_out_tensor_tensor_double_generator)
  LOAD_SYMBOL(_lantern_normal_out_tensor_double_tensor_generator)
  LOAD_SYMBOL(_lantern_normal_out_tensor_tensor_tensor_generator)
  LOAD_SYMBOL(_lantern_normal_out_tensor_double_double_intarrayref_generator)
  LOAD_SYMBOL(_lantern_alias_tensor)
  LOAD_SYMBOL(_lantern_Tensor_alias_tensor)
  LOAD_SYMBOL(_lantern__addr_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern__addr__tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern__addr_out_tensor_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern__index_copy__tensor_intt_tensor_tensor)
  LOAD_SYMBOL(_lantern__cumsum_tensor_intt)
  LOAD_SYMBOL(_lantern__cumsum_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__cumprod_tensor_intt)
  LOAD_SYMBOL(_lantern__cumprod_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern__var_tensor_bool)
  LOAD_SYMBOL(_lantern__std_tensor_bool)
  LOAD_SYMBOL(_lantern__amp_non_finite_check_and_unscale__tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern__amp_update_scale_tensor_tensor_tensor_double_double_intt)
  LOAD_SYMBOL(_lantern__cat_tensorlist_intt)
  LOAD_SYMBOL(_lantern__cat_out_tensor_tensorlist_intt)
  LOAD_SYMBOL(_lantern__mode_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__mode_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__max_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__max_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__min_tensor_intt_bool)
  LOAD_SYMBOL(_lantern__min_out_tensor_tensor_tensor_intt_bool)
  LOAD_SYMBOL(_lantern_mse_loss_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_mse_loss_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_mse_loss_backward_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_mse_loss_backward_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_l1_loss_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_l1_loss_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_l1_loss_backward_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_multi_margin_loss_out_tensor_tensor_tensor_scalar_scalar_tensor_intt)
  LOAD_SYMBOL(_lantern_multi_margin_loss_tensor_tensor_scalar_scalar_tensor_intt)
  LOAD_SYMBOL(_lantern_multi_margin_loss_backward_out_tensor_tensor_tensor_tensor_scalar_scalar_tensor_intt)
  LOAD_SYMBOL(_lantern_multi_margin_loss_backward_tensor_tensor_tensor_scalar_scalar_tensor_intt)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_forward_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_forward_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_multilabel_margin_loss_backward_tensor_tensor_tensor_intt_tensor)
  LOAD_SYMBOL(_lantern_nll_loss_out_tensor_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss_forward_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor)
  LOAD_SYMBOL(_lantern_nll_loss_backward_tensor_tensor_tensor_tensor_intt_intt_tensor)
  LOAD_SYMBOL(_lantern_nll_loss2d_out_tensor_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss2d_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss2d_forward_out_tensor_tensor_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss2d_forward_tensor_tensor_tensor_intt_intt)
  LOAD_SYMBOL(_lantern_nll_loss2d_backward_out_tensor_tensor_tensor_tensor_tensor_intt_intt_tensor)
  LOAD_SYMBOL(_lantern_nll_loss2d_backward_tensor_tensor_tensor_tensor_intt_intt_tensor)
  LOAD_SYMBOL(_lantern_smooth_l1_loss_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_smooth_l1_loss_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_smooth_l1_loss_backward_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_smooth_l1_loss_backward_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_soft_margin_loss_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_soft_margin_loss_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_soft_margin_loss_backward_out_tensor_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_soft_margin_loss_backward_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_elu_out_tensor_tensor_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_elu_tensor_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_elu_backward_out_tensor_tensor_scalar_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_elu_backward_tensor_scalar_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_elu__tensor_scalar_scalar_scalar)
  LOAD_SYMBOL(_lantern_glu_out_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_glu_tensor_intt)
  LOAD_SYMBOL(_lantern_glu_backward_out_tensor_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_glu_backward_tensor_tensor_intt)
  LOAD_SYMBOL(_lantern_hardsigmoid_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_hardsigmoid_tensor)
  LOAD_SYMBOL(_lantern_hardsigmoid__tensor)
  LOAD_SYMBOL(_lantern_hardsigmoid_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_hardtanh_out_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_hardtanh_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_hardtanh_backward_out_tensor_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_hardtanh_backward_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_hardtanh__tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_leaky_relu_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_leaky_relu_tensor_scalar)
  LOAD_SYMBOL(_lantern_leaky_relu_backward_tensor_tensor_scalar_bool)
  LOAD_SYMBOL(_lantern_leaky_relu__tensor_scalar)
  LOAD_SYMBOL(_lantern_log_sigmoid_out_tensor_tensor)
  LOAD_SYMBOL(_lantern_log_sigmoid_tensor)
  LOAD_SYMBOL(_lantern_log_sigmoid_forward_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_log_sigmoid_forward_tensor)
  LOAD_SYMBOL(_lantern_log_sigmoid_backward_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_log_sigmoid_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_rrelu_with_noise_out_tensor_tensor_tensor_scalar_scalar_bool_generator)
  LOAD_SYMBOL(_lantern_rrelu_with_noise_tensor_tensor_scalar_scalar_bool_generator)
  LOAD_SYMBOL(_lantern_rrelu_with_noise_backward_tensor_tensor_tensor_scalar_scalar_bool_bool)
  LOAD_SYMBOL(_lantern_rrelu_with_noise__tensor_tensor_scalar_scalar_bool_generator)
  LOAD_SYMBOL(_lantern_softplus_out_tensor_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_softplus_tensor_scalar_scalar)
  LOAD_SYMBOL(_lantern_softplus_backward_out_tensor_tensor_tensor_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_softplus_backward_tensor_tensor_scalar_scalar_tensor)
  LOAD_SYMBOL(_lantern_softshrink_out_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_softshrink_tensor_scalar)
  LOAD_SYMBOL(_lantern_softshrink_backward_out_tensor_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_softshrink_backward_tensor_tensor_scalar)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool2d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_mkldnn_adaptive_avg_pool2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern__adaptive_avg_pool2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern__adaptive_avg_pool2d_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool3d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool3d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool3d_backward_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_avg_pool3d_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_max_pool2d_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_max_pool2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_max_pool2d_backward_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_max_pool2d_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_max_pool3d_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_max_pool3d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_adaptive_max_pool3d_backward_out_tensor_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_adaptive_max_pool3d_backward_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_avg_pool2d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool2d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool2d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool3d_out_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool3d_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_avg_pool3d_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_bool_bool_intt)
  LOAD_SYMBOL(_lantern_fractional_max_pool2d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool2d_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool2d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool2d_backward_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool3d_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool3d_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_fractional_max_pool3d_backward_tensor_tensor_intarrayref_intarrayref_tensor)
  LOAD_SYMBOL(_lantern_max_pool2d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool2d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool2d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)
  LOAD_SYMBOL(_lantern_max_pool2d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)
  LOAD_SYMBOL(_lantern_max_pool3d_with_indices_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool3d_with_indices_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool)
  LOAD_SYMBOL(_lantern_max_pool3d_with_indices_backward_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)
  LOAD_SYMBOL(_lantern_max_pool3d_with_indices_backward_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_bool_tensor)
  LOAD_SYMBOL(_lantern_max_unpool2d_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool2d_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool2d_backward_out_tensor_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool2d_backward_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool3d_out_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool3d_tensor_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool3d_backward_out_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_max_unpool3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad1d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad1d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad1d_backward_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad1d_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad2d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad2d_backward_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_reflection_pad2d_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad1d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad1d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad1d_backward_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad1d_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad2d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad2d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad2d_backward_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad2d_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad3d_out_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad3d_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad3d_backward_out_tensor_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_replication_pad3d_backward_tensor_tensor_intarrayref)
  LOAD_SYMBOL(_lantern_upsample_linear1d_out_tensor_tensor_intarrayref_bool_double)
  LOAD_SYMBOL(_lantern_upsample_linear1d_tensor_intarrayref_bool_double)
  LOAD_SYMBOL(_lantern_upsample_linear1d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double)
  LOAD_SYMBOL(_lantern_upsample_linear1d_backward_tensor_intarrayref_intarrayref_bool_double)
  LOAD_SYMBOL(_lantern_upsample_bilinear2d_out_tensor_tensor_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bilinear2d_tensor_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bilinear2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bilinear2d_backward_tensor_intarrayref_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bicubic2d_out_tensor_tensor_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bicubic2d_tensor_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bicubic2d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_bicubic2d_backward_tensor_intarrayref_intarrayref_bool_double_double)
  LOAD_SYMBOL(_lantern_upsample_trilinear3d_out_tensor_tensor_intarrayref_bool_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_trilinear3d_tensor_intarrayref_bool_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_trilinear3d_backward_out_tensor_tensor_intarrayref_intarrayref_bool_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_trilinear3d_backward_tensor_intarrayref_intarrayref_bool_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest1d_out_tensor_tensor_intarrayref_double)
  LOAD_SYMBOL(_lantern_upsample_nearest1d_tensor_intarrayref_double)
  LOAD_SYMBOL(_lantern_upsample_nearest1d_backward_out_tensor_tensor_intarrayref_intarrayref_double)
  LOAD_SYMBOL(_lantern_upsample_nearest1d_backward_tensor_intarrayref_intarrayref_double)
  LOAD_SYMBOL(_lantern_upsample_nearest2d_out_tensor_tensor_intarrayref_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest2d_tensor_intarrayref_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest2d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest2d_backward_tensor_intarrayref_intarrayref_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest3d_out_tensor_tensor_intarrayref_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest3d_tensor_intarrayref_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest3d_backward_out_tensor_tensor_intarrayref_intarrayref_double_double_double)
  LOAD_SYMBOL(_lantern_upsample_nearest3d_backward_tensor_intarrayref_intarrayref_double_double_double)
  LOAD_SYMBOL(_lantern_sigmoid_backward_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_sigmoid_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_tanh_backward_out_tensor_tensor_tensor)
  LOAD_SYMBOL(_lantern_tanh_backward_tensor_tensor)
  LOAD_SYMBOL(_lantern_slow_conv_transpose2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_transpose2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_transpose2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor)
  LOAD_SYMBOL(_lantern_slow_conv_transpose2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern_slow_conv_transpose3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_transpose3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_transpose3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor)
  LOAD_SYMBOL(_lantern_slow_conv_transpose3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern_thnn_conv2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv2d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv2d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor)
  LOAD_SYMBOL(_lantern_thnn_conv2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_forward_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_backward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_thnn_conv_depthwise2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)
  LOAD_SYMBOL(_lantern_slow_conv3d_out_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv3d_forward_out_tensor_tensor_tensor_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv3d_forward_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv3d_backward_out_tensor_tensor_tensor_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor)
  LOAD_SYMBOL(_lantern_slow_conv3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_tensor_tensor_stdarraybool)
  LOAD_SYMBOL(_lantern_slow_conv_dilated2d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_dilated2d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)
  LOAD_SYMBOL(_lantern_slow_conv_dilated3d_tensor_tensor_intarrayref_tensor_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_slow_conv_dilated3d_backward_tensor_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_stdarraybool)
  LOAD_SYMBOL(_lantern_col2im_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_col2im_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_col2im_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_col2im_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_im2col_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_im2col_tensor_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_im2col_backward_out_tensor_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_im2col_backward_tensor_intarrayref_intarrayref_intarrayref_intarrayref_intarrayref)
  LOAD_SYMBOL(_lantern_isfinite_tensor)
  LOAD_SYMBOL(_lantern_isinf_tensor)
  /* Autogen Symbols -- End */

  return true;
}

#else

extern bool lanternInit(const std::string &libPath, std::string *pError);
extern bool laternCloseLibrary(void *pLib, std::string *pError);

#endif
#endif
