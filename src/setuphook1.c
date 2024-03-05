//<FLAGS>
//#define __GPU
//#define __NOPROTO
//<\FLAGS>

//<INCLUDES>
#include "fargo3d.h"
//<\INCLUDES>

void SetupHook1_cpu(real dt) {  // Empty function. May be used as a template for custom function in setup directory.

//<USER_DEFINED>
INPUT(Energy);
INPUT2D(Energy0);
INPUT2D(OmegaOverBeta);
INPUT(Density);
OUTPUT(Energy);
//<\USER_DEFINED>

//<EXTERNAL>
  int pitch  = Pitch_cpu;
  int pitch2D  = Pitch2D;
  int stride = Stride_cpu;
  int size_x = Nx+2*NGHX;
  int size_y = Ny+2*NGHY;
  int size_z = Nz+2*NGHZ;
  real* e   = Energy->field_cpu;
  real* e0   = Energy0->field_cpu;
  real* OoB = OmegaOverBeta->field_cpu;
  real* rho = Density->field_cpu;
//<\EXTERNAL>
  
//<INTERNAL>
  int i; //Variables reserved
  int j; //for the topology
  int k; //of the kernels
  int ll;
  int ll2D;
//<\INTERNAL>

//<MAIN_LOOP>

  i = j = k = 0;

#ifdef Z
  for(k=1; k<size_z; k++) {
#endif
#ifdef Y
    for(j=1; j<size_y; j++) {
#endif
#ifdef X
      for(i=0; i<size_x; i++) {
#endif
//<#>
ll=l;
ll2D = l2D;
e[ll] = (e[ll]+dt*OoB[ll2D]*e0[ll2D]*rho[ll])/(1.0+dt*OoB[ll2D]);
//<\#>
#ifdef X
      }
#endif
#ifdef Y
    }
#endif
#ifdef Z
  }
#endif
//<\MAIN_LOOP>
}
