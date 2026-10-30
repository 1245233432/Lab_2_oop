#include "dist_class.h"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

namespace distribution {

	double Huber::phi(double x) const {
		return exp(-0.5 * x * x) / sqrt(2.0 * PI);
	}

	double Huber::Phi(double x) const {
		return 0.5 * (1.0 + erf(x / sqrt(2.0)));
	}

	void Huber::update_K_P() {
		K = (2.0 / nu) * phi(nu) + 2.0 * Phi(nu) - 1.0;
		P = (2.0 * Phi(nu) - 1.0) / K;
	}

	void Huber::validate() const {
		if (nu <= 0.0) {
			throw std::invalid_argument("Nu должен быть больше 0");
		}
		if (lam <= 0.0) {
			throw std::invalid_argument("Lambda должен быть больше 0");
		}
	}

	double Huber::generate_standart() const {
		double r1;
		do {
			r1 = static_cast<double>(rand()) / RAND_MAX;
		} while (r1 == 0.0 || r1 == 1.0);

		if (r1 <= P) {
			while (true) {
				double r2, r3;
				do { r2 = static_cast<double>(rand()) / RAND_MAX; } while (r2 == 0.0 || r2 == 1.0);
				do { r3 = static_cast<double>(rand()) / RAND_MAX; } while (r3 == 0.0 || r3 == 1.0);

				double x1 = sqrt(-2.0 * log(r2)) * cos(2.0 * PI * r3);

				if (fabs(x1) <= nu) {
					return x1;
				}
			}
		}

		double r4;
		do {
			r4 = static_cast<double>(rand()) / RAND_MAX;
		} while (r4 == 0.0 || r4 == 1.0);

		double x2 = nu - (log(r4) / nu);

		if (r1 < (1.0 + P) / 2.0) {
			return x2;
		}
		else {
			return -x2;
		}
	}

	Huber::Huber() : nu(1.0), mu(0.0), lam(1.0) {
		update_K_P();
	}

	Huber::Huber(double nu, double mu, double lam) : nu(nu), mu(mu), lam(lam) {
		validate();
		update_K_P();
	}

	Huber::Huber(const std::string& filename) {
		load(filename);
	}

	void Huber::set_nu(double nu) {
		if (nu <= 0.0) {
			throw std::invalid_argument("Nu должен быть больше 0");
		}
		this->nu = nu;
		update_K_P();
	}

	void Huber::set_mu(double mu) {
		this->mu = mu;
		// K и P не зависят от mu
	}

	void Huber::set_lam(double lam) {
		if (lam <= 0.0) {
			throw std::invalid_argument("Lambda должен быть больше 0");
		}
		this->lam = lam;
		// K и P не зависят от lam
	}

	void Huber::set_params(double nu, double mu, double lam) {
		if (nu <= 0.0) {
			throw std::invalid_argument("Nu должен быть больше 0");
		}
		if (lam <= 0.0) {
			throw std::invalid_argument("Lambda должен быть больше 0");
		}
		this->nu = nu;
		this->mu = mu;
		this->lam = lam;
		update_K_P();
	}

	double Huber::get_nu() const { 
		return nu; 
	}

	double Huber::get_mu() const { 
		return mu; 
	}

	double Huber::get_lam() const { 
		return lam; 
	}

	double Huber::get_K() const { 
		return K; 
	}

	double Huber::get_P() const { 
		return P; 
	}

	double Huber::get_density(double x) const {
		double z = (x - mu) / lam;
		double c = 1.0 / (K * lam * sqrt(2.0 * PI));

		if (fabs(z) <= nu) {
			return c * exp(-0.5 * z * z);
		}
		else {
			return c * exp(nu * nu * 0.5 - nu * fabs(z));
		}
	}

	double Huber::get_expected_value() const {
		return mu;
	}

	double Huber::get_dispersion() const {
		double sigma = 1.0 + ((2.0 * phi(nu) * (nu * nu + 2.0)) / (nu * nu * nu * K));
		return lam * lam * sigma;
	}

	double Huber::get_asymmetry() const {
		return 0.0;   // стандартное распределение симметрично
	}

	double Huber::get_excess() const {
		double sigma2 = 1.0 + ((2.0 * phi(nu) * (nu * nu + 2.0)) / (nu * nu * nu * K));
		double sigma4 = sigma2 * sigma2;

		double a = 24.0 / (nu * nu * nu * nu * nu);
		double b = 24.0 / (nu * nu * nu);
		double c = 12.0 / nu;

		double gamma2 = (1.0 / (sigma4 * K)) * (3.0 * (2.0 * Phi(nu) - 1.0) + 2.0 * phi(nu) * (a + b + c + nu)) - 3.0;
		return gamma2;
	}

	double Huber::get_random_value() const {
		double x = generate_standart();
		return mu + x * lam;
	}

	void Huber::save(const std::string& filename) const {
		std::ofstream out(filename);
		if (!out) {
			throw std::runtime_error("Не удается открыть файл для записи");
		}
		out << nu << " " << mu << " " << lam << std::endl;
		out.close();
	}

	void Huber::load(const std::string& filename) {
		std::ifstream in(filename);
		if (!in) {
			throw std::runtime_error("Не удается открыть файл для чтения");
		}
		double n, m, l;
		if (!(in >> n >> m >> l)) {
			throw std::runtime_error("Неверный формат файла для чтения");
		}
		set_params(n, m, l);
	}
}