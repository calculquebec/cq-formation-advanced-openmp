PROGRAM blockmatrix

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: m = 640, n = 800
DOUBLE PRECISION, ALLOCATABLE :: x(:,:,:)
INTEGER :: i, j, k, mlocal, tid, tot
DOUBLE PRECISION :: t1, t2, scale

    scale = 2.0

!$omp parallel default(none) private(i,j,k,x,tid,tot,mlocal) shared(scale,t1)

    tid = omp_get_thread_num()
    tot = omp_get_num_threads()
    mlocal = (tid+1)*m/tot-tid*m/tot
    ALLOCATE(x(mlocal,n,n))

    do k = 2, n
       do j = 2, n
          do i = 1, mlocal
             x(i,j,k) = 1d0
          end do
       end do
    end do

!$omp barrier
!$omp master

    t1 = OMP_GET_WTIME()

!$omp end master

    do k = 2, n
       do j = 2, n
          do i = 1, mlocal
             x(i,j,k) = x(i,j,k-1) + x(i,j-1,k)*scale
          end do
       end do
    end do
!$omp end parallel

    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Blockmatrix Time =', t2 - t1, " on ", omp_get_max_threads(), "threads"

END PROGRAM blockmatrix
