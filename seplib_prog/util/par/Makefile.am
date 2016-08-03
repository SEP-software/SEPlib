
EXTRA_DIST =  Copy_split.csep Copy_join.csep Patch_split.csep \
   Patch_join.csep Sep3d_split.csep Send_msg.csep Solver_ops_split.csep Planewave_split.csep


bin_PROGRAMS =
if HAVE_MPI
bin_PROGRAMS +=Copy_split Copy_join  Send_msg \
  Patch_split Patch_join Sep3d_split Solver_ops_split \
  Split_first Join_first Planewave_split
endif
                                                                                      


#if HAVE_MPI
#bin_PROGRAMS += DistribM  CollectM PartitionM   CombineM PartM \
#  Copy_split Copy_join Distribute_split Distribute_join #Patch_split Patch_join
#endif

LDADD=${SEPLIB3D}

%.o: %.c
	$(COMPILE) $(MPI_FLAGS) -c -o $@ $<
                                                                                
%.lo: %.c
	$(LTCOMPILE) $(MPI_FLAGS) -c -o $@ $<


include $(top_srcdir)/include/fortran.rules

                                                                                

Send_msg_LDADD=-lsep


Copy_join_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm
Copy_split_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm
Planewave_split_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm

Patch_split_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm
Split_first_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm
Join_first_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm
Patch_join_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm


Sep3d_split_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm

Solver_ops_split_LDADD = -lsuperset_mpi -lsepaux ${SEPLIB3D} -lseppar_mpi $(MPI_LD) -lm


