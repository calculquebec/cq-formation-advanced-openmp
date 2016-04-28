PROGRAM blockmatrix

USE omp_lib
IMPLICIT NONE

INTEGER, PARAMETER :: m = 640, n = 800
DOUBLE PRECISION, ALLOCATABLE :: x(:,:,:)
INTEGER :: i, j, k
DOUBLE PRECISION :: t1, t2, scale

    ALLOCATE(x(m,n,n))
    do k = 2, n
       do j = 2, n
!$omp parallel do default(shared) private(i)
          do i = 1, m
             x(i,j,k) = 1d0
          end do
!$omp end parallel do
       end do
    end do

    t1 = OMP_GET_WTIME()
    scale = 2.0

    do k = 2, n
       do j = 2, n
!$omp parallel do default(shared) private(i)
          do i = 1, m
             x(i,j,k) = x(i,j,k-1) + x(i,j-1,k)*scale
          end do
!$omp end parallel do
       end do
    end do

    t2 = OMP_GET_WTIME()

    WRITE(*,*) 'Blockmatrix Time =', t2 - t1, " on ", omp_get_max_threads(), "threads"

END PROGRAM blockmatrix
