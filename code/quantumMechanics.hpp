// Author Fredrik Jadebeck
//
// Headerfile for the quantumMechanics.py port
#ifndef QUANTUMMECHANICS_H
#define QUANTUMMECHANICS_H

#include <Eigen/Core>
#include <map>
#include <string>
#include <vector>

using namespace Eigen;

std::vector<double> gen_m(const int& N);
int kronecker(const double& m, const double& n);
double mSxn(const double& m, const double& n, const double& S);
double mSzn(const double& m, const double& n, const double& S);
Matrix<double, Dynamic, Dynamic> Sx(const int& N);
Matrix<double, Dynamic, Dynamic> Sz(const int& N);

//class prototypes
class state;
class ketBra;
class dm;

//class definitions
class state
{
public:
  std::vector<std::string> quantumState;

  state();
  state(std::string spins);
  double getNorm() const;
  double scalar_product(const state& other) const;
  ketBra tensor_product(const state& other) const;
  state operator+(const state& other);
  bool operator==(const state& other) const;
};

class ketBra
{
public:
  double amplitude;
  state tket;
  state tbra;
  
  ketBra(const state& ket, const state& bra);
  ketBra multiply_with(const ketBra& other);
};

class dm
{
public:
  std::map<ketBra, double> rho;
  int N;
  int S;
  std::vector<double> ms;
  std::vector<state> z;

  dm(Matrix<double, Dynamic, Dynamic> rho,
     std::vector<Matrix<double, Dynamic, Dynamic> > zeemanBasis,
     const int& N);
  Matrix<double, Dynamic, Dynamic> nparray();
  dm ptrace(const int& k);
};

void zeeman();

#endif
