PROGRAM blockmatrix

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: m = 640, n = 800
DOUBLE PRECISION, ALLOCATABLE :: x(:,:,:)
INTEGER :: i, j, k
DOUBLE PRECISION :: t1, t2, scale

    ALLOCATE(x(m,n,n))

!$omp parallel default(none) private(i,j,k) shared(x)
    do k = 2, n
       do j = 2, n
!$omp do
          do i = 1, m
             x(i,j,k) = 1d0
          end do
!$omp end do nowait
       end do
    end do
!$omp end parallel

    t1 = OMP_GET_WTIME()
    scale = 2.0

!$omp parallel default(none) private(i,j,k) shared(x,scale)
    do k = 2, n
       do j = 2, n
!$omp do
          do i = 1, m
             x(i,j,k) = x(i,j,k-1) + x(i,j-1,k)*scale
          end do
!$omp end do nowait
       end do
    end do
!$omp end parallel

    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Blockmatrix Time =', t2 - t1, " on ", omp_get_max_threads(), "threads"

END PROGRAM blockmatrix
