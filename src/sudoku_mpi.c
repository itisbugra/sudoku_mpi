#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "defs.h"
#include "convert.h"
#include "util.h"
#include "vertical.h"
#include "horizontal.h"
#include "subbox.h"
#include "breakdown.h"

//  Kindergarten
// static int32_t kMATRIX[SIZE][SIZE] = {
//   { 0, 5, 2, 1, 3, 0, 0, 0, 9 },
//   { 9, 0, 0, 0, 0, 5, 8, 3, 0 },
//   { 0, 7, 0, 6, 0, 4, 0, 0, 2 },
//   { 0, 0, 1, 9, 0, 2, 0, 7, 0 },
//   { 3, 6, 9, 0, 5, 0, 1, 0, 8 },
//   { 0, 4, 0, 0, 8, 0, 6, 0, 5 },
//   { 6, 0, 8, 7, 0, 0, 9, 0, 1 },
//   { 7, 3, 0, 8, 0, 0, 0, 4, 0 },
//   { 0, 0, 4, 0, 2, 6, 3, 0, 0 },
//};

//  Elementary
static int32_t kMATRIX[SIZE][SIZE] = {
  { 0, 2, 6, 0, 9, 0, 0, 0, 0 },
  { 3, 0, 7, 2, 0, 0, 0, 0, 8 },
  { 0, 0, 0, 0, 7, 1, 0, 0, 4 },
  { 8, 0, 0, 0, 0, 0, 0, 9 ,0 },
  { 5, 9, 0, 0, 1, 6, 0, 2, 0 },
  { 0, 0, 0, 0, 4, 3, 1, 0, 0 },
  { 0, 0, 0, 4, 0, 0, 0, 5, 2 },
  { 0, 0, 8, 0, 0, 0, 0, 0, 3 },
  { 7, 0, 4, 5, 0, 0, 6, 0, 0 },
};

//  High school
// static int32_t kMATRIX[SIZE][SIZE] = {
//   { 0, 7, 0, 0, 2, 0, 0, 0, 0 },
//   { 0, 0, 0, 3, 0, 6, 9, 0, 0 },
//   { 1, 0, 0, 0, 5, 0, 0, 0, 3 },
//   { 4, 0, 0, 0, 0, 0, 3, 0, 0 },
//   { 0, 8, 0, 0, 0, 0, 1, 6, 0 },
//   { 0, 0, 0, 0, 8, 0, 5, 9, 0 },
//   { 0, 0, 2, 1, 0, 0, 0, 0, 0 },
//   { 5, 1, 0, 8, 0, 0, 0, 0, 0 },
//   { 8, 6, 0, 7, 0, 0, 0, 2, 0 },
// };

//  Graduate
// static int32_t kMATRIX[SIZE][SIZE] = {
//   { 0, 2, 6, 0, 0, 8, 0, 0, 0 },
//   { 5, 8, 9, 0, 0, 0, 0, 0, 7 },
//   { 0, 0, 0, 0, 0, 0, 0, 1, 0 },
//   { 0, 0, 4, 0, 7, 9, 0, 0, 0 },
//   { 0, 0, 0, 0, 0, 6, 8, 4, 0 },
//   { 0, 3, 2, 0, 0, 0, 0, 0, 0 },
//   { 0, 0, 0, 8, 3, 0, 0, 7, 0 },
//   { 0, 1, 0, 0, 0, 0, 0, 0, 5 },
//   { 6, 9, 0, 0, 0, 0, 0, 0, 0 },
// };

int32_t main(int32_t argc, char **argv) {
  MPI_Init(&argc, &argv);

  int comm_size;
  int comm_rank;
  bool is_master = false;

  if (MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS) {
    fprintf(stderr, "%s\n", "error: cannot get rank");
  }

  if (MPI_Comm_size(MPI_COMM_WORLD, &comm_size) != MPI_SUCCESS) {
    fprintf(stderr, "%s\n", "error: cannot get size");
  }

  if (comm_rank == 0) {
    is_master = true;
  }

  SDK_Import(kMATRIX);

retry:
  if (comm_rank == 0) {
    SDK_Mark_Vertical_Availables(kMATRIX);

    int32_t tmp[SIZE][SIZE];

    MPI_Recv(tmp, SIZE * SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD, NULL);
    SDK_Apply(kMATRIX, tmp);
    MPI_Recv(tmp, SIZE * SIZE, MPI_INT, 2, 0, MPI_COMM_WORLD, NULL);
    SDK_Apply(kMATRIX, tmp);

  } else if (comm_rank == 1) {
    SDK_Mark_Horizontal_Availables(kMATRIX);

    MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else if (comm_rank == 2) {
    SDK_Mark_Subbox_Availables(kMATRIX);

    MPI_Send(kMATRIX, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    goto bailout;
  }

  MPI_Bcast(kMATRIX, SIZE * SIZE, MPI_INT, 0, MPI_COMM_WORLD);

  if (SDK_Check_Breakdown(kMATRIX)) {
    if (is_master) {
      SDK_Pretty_Print(kMATRIX);
    }
  } else {
    goto retry;
  }

bailout:
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Finalize();
}
