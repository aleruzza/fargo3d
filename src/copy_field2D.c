#include "fargo3d.h"

void copy_field2D_cpu(Field2D *Dst, Field2D *Src) {

  real *dst = Dst->field_cpu;
  real *src = Src->field_cpu;
  
  INPUT2D(Src);
  OUTPUT2D(Dst);
  memcpy (dst, src, sizeof(real)*(Ny+2*NGHY)*(Nz+2*NGHZ));

}

void copy_field2D_gpu(Field2D *Dst, Field2D *Src) {

#ifdef GPU
  int width, height, pitch;

  real *dst = Dst->field_gpu;
  real *src = Src->field_gpu;

  Input2D_GPU(Src, __LINE__, __FILE__);
  Output2D_GPU(Dst, __LINE__, __FILE__);
  
    pitch = Stride_gpu * sizeof(real);
    width = (Ny+2*NGHY)*sizeof(real);
    height = Nz+2*NGHZ;

  cudaMemcpy2D (dst, pitch, src, pitch, width, height ,cudaMemcpyDeviceToDevice);
#endif

}
