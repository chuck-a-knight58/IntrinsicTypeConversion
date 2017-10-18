#!/bin/bash

#SBATCH --partition=batch
#SBATCH --job-name=multiple_job_example
#SBATCH --comment="Run jobs independently across all allocated nodes"

#SBATCH --nodes=2
#SBATCH --ntasks=32

srun --mpi=pmi2 --ntasks=32 --nodes=2 example
