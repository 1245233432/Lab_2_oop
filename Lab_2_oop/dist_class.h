#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <cmath>

#define PI 3.14159265358979323846

namespace distribution {
	class Huber {
	private:
		double nu; // форма, nu > 0
		double mu; // сдвиг
		double lam; // масштаб, lam > 0
		double K;
		double P; // вероятность P{x в центральном интервале}

		double phi(double x) const;
		double Phi(double x) const;
		double generate_standart() const;

		void update_K_P(); // пересчет K и P при изменении параметров
		void validate() const; // проверка корректности параметров

	public:
		Huber();
		Huber(double nu, double mu, double lam);
		explicit Huber(const std::string& filename);

		void set_nu(double nu); // сеттеры
		void set_mu(double mu);
		void set_lam(double lam);
		void set_params(double nu, double mu, double lam);

		double get_nu() const; // геттеры
		double get_mu() const;
		double get_lam() const;
		double get_K() const;
		double get_P() const;
		double get_density(double x) const;
		double get_expected_value() const;
		double get_dispersion() const;
		double get_asymmetry() const;
		double get_excess() const;
		double get_random_value() const; // моделирование тоже тут

		void save(const std::string& filename) const; // персистентность, т.е. единый формат файлов 
		void load(const std::string& filename);
	};
}