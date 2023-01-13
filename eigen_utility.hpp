#include "gnuplot.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>

template<typename T>
void sparseDisplay(Eigen::SparseMatrix<T> matrix)
{
    GnuplotPipe gp;
    std::fstream ofs;
    ofs.open("sparse_data.dat", std::ios::out);
    size_t row = matrix.rows();
    size_t col = matrix.cols();
    for (int k = 0; k < matrix.outerSize(); ++k)
        for (Eigen::SparseMatrix<T>::InnerIterator it(matrix, k); it; ++it)
        {
            ofs << it.col() << " " << -it.row() << "\n";
        }
    gp.sendLine("set terminal wxt size 640,480");
    gp.sendLine("set xrange [-1:" + std::to_string(col) + "]");
    gp.sendLine("set yrange [-" + std::to_string(row + 1) + ":1]");
    gp.sendLine("plot 'sparse_data.dat' using 1:2");
    return ;
}