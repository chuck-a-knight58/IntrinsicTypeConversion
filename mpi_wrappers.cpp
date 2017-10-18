#include <mpi.h>
#include "mpi_wrappers.h"
#include <stdexcept>

static MPI_Datatype ConvertType(Abstraction::DataType type)
{
	switch (type)
	{
	case Abstraction::type_char: return MPI_CHAR;
	case Abstraction::type_unsigned_char: return MPI_UNSIGNED_CHAR;
	case Abstraction::type_short: return MPI_SHORT;
	case Abstraction::type_unsigned_short: return MPI_UNSIGNED_SHORT;
	case Abstraction::type_int: return MPI_INT;
	case Abstraction::type_unsigned_int: return MPI_UNSIGNED;
	case Abstraction::type_long: return MPI_LONG;
	case Abstraction::type_unsigned_long: return MPI_UNSIGNED_LONG;
	case Abstraction::type_float: return MPI_FLOAT;
	case Abstraction::type_double: return MPI_DOUBLE;
	};
	throw std::runtime_error("MPI_Datatype Convert(Abstraction::DataType) failed");
}

void SendImpl(void *data, int count, Abstraction::DataType type, int dest, int tag)
{
	if (MPI_Send(data, count, ConvertType(type), dest, tag, MPI_COMM_WORLD) != MPI_SUCCESS)
	{
		throw std::runtime_error("MPI_Send failed");
	}
}

void ReceiveImpl(void *data, int count, Abstraction::DataType type, int src, int tag)
{
	MPI_Status status;
	if (MPI_Recv(data, count, ConvertType(type), src, tag, MPI_COMM_WORLD, &status) != MPI_SUCCESS)
	{
		throw std::runtime_error("MPI_Recv failed");
	}
}
