#include "dist_class.h"

#include <iostream>
#include <ctime>
#include <limits>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>

int testing() {
	short choice;
	std::cout << std::endl;
	std::cout << "1. Тест по данным из таблицы к ЛР 1" << std::endl;
	std::cout << "2. Ввод с клавиатуры" << std::endl;
	std::cout << "3. Ввод из файла" << std::endl;
	std::cout << "4. Выход" << std::endl;
	std::cin >> choice; std::cout << std::endl;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Неверный ввод" << std::endl;
		return 0;
	}
	if (choice < 1 || choice > 4) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Неверный ввод" << std::endl;
		return 0;
	}

	switch (choice) {
	case 1: {
		{
			distribution::Huber h(0.5, 0.0, 1.0);
			double x = 0.0;

			std::cout << std::endl << "Обычный тест" << std::endl;
			std::cout << "x = " << x << std::endl;
			std::cout << "Форма nu = " << h.get_nu() << std::endl;
			std::cout << "Сдвиг mu = " << h.get_mu() << std::endl;
			std::cout << "Масштаб lambda = " << h.get_lam() << std::endl << std::endl;

			std::cout << "Плотность f(x) = " << h.get_density(x)
				<< "; ожидалось: f0 = 0.223" << std::endl;
			std::cout << "Мат. ожидание M[ksi] = " << h.get_expected_value()
				<< "; ожидалось: " << h.get_mu() << std::endl;
			std::cout << "Дисперсия D[ksi] = " << h.get_dispersion()
				<< "; ожидалось: sigma^2 = 8.08" << std::endl;
			std::cout << "Асимметрия gamma1 = " << h.get_asymmetry()
				<< "; ожидалось: gamma1 = 0.0" << std::endl;
			std::cout << "Эксцесс gamma2 = " << h.get_excess()
				<< "; ожидалось: gamma2 = 2.94" << std::endl;
			std::cout << "P{x в центральном интервале} =  " << h.get_P()
				<< "; ожидалось: 0.214" << std::endl << std::endl;
		}

		{
			distribution::Huber h(1.5, 0.0, 2.0);
			double x = 0.0;

			std::cout << "Масштабное преобразование" << std::endl;
			std::cout << "x = " << x << std::endl;
			std::cout << "Форма nu = " << h.get_nu() << std::endl;
			std::cout << "Сдвиг mu = " << h.get_mu() << std::endl;
			std::cout << "Масштаб lambda = " << h.get_lam() << std::endl << std::endl;

			std::cout << "Плотность f(x) = " << h.get_density(x)
				<< "; ожидалось: f0/lambda = 0.192" << std::endl;
			std::cout << "Мат. ожидание M[ksi] = " << h.get_expected_value()
				<< "; ожидалось: " << h.get_mu() << std::endl;
			std::cout << "Дисперсия D[ksi] = " << h.get_dispersion()
				<< "; ожидалось: sigma^2 * lambda^2 = 5.24" << std::endl;
			std::cout << "Асимметрия gamma1 = " << h.get_asymmetry()
				<< "; ожидалось: gamma1 = 0.0" << std::endl;
			std::cout << "Эксцесс gamma2 = " << h.get_excess()
				<< "; ожидалось: gamma2 = 1.30" << std::endl;
			std::cout << "P{x в центральном интервале} =  " << h.get_P()
				<< "; ожидалось: 0.834" << std::endl << std::endl;
		}

		{
			distribution::Huber h(3.0, 2.0, 2.0);
			double x = h.get_mu();

			std::cout << "Сдвиг-масштабное преобразование" << std::endl;
			std::cout << "x = mu = " << x << std::endl;
			std::cout << "Форма nu = " << h.get_nu() << std::endl;
			std::cout << "Сдвиг mu = " << h.get_mu() << std::endl;
			std::cout << "Масштаб lambda = " << h.get_lam() << std::endl << std::endl;

			std::cout << "Results:" << std::endl;
			std::cout << "Плотность f(x) = " << h.get_density(x)
				<< "; ожидалось: f0/lambda = 0.1995" << std::endl;
			std::cout << "Мат. ожидание M[ksi] = " << h.get_expected_value()
				<< "; ожидалось: " << h.get_mu() << std::endl;
			std::cout << "Дисперсия D[ksi] = " << h.get_dispersion()
				<< "; ожидалось: sigma^2 * lambda^2 = 4.00" << std::endl;
			std::cout << "Асимметрия gamma1 = " << h.get_asymmetry()
				<< "; ожидалось: gamma1 = 0.0" << std::endl;
			std::cout << "Эксцесс gamma2 = " << h.get_excess()
				<< "; ожидалось: gamma2 = 0.04" << std::endl;
			std::cout << "P{x в центральном интервале} =  " << h.get_P()
				<< "; ожидалось: 0.997" << std::endl << std::endl;
		}

		return 1;
	}
	case 2: {
		double x, nu, mu, lam;
		std::cout << std::endl;
		std::cout << "Введите параметры" << std::endl;
		std::cout << "x = ";
		std::cin >> x;
		std::cout << "nu = ";
		std::cin >> nu;
		std::cout << "mu = ";
		std::cin >> mu;
		std::cout << "lambda = ";
		std::cin >> lam;

		try {
			distribution::Huber h(nu, mu, lam);

			std::cout << std::endl << "Result:" << std::endl;
			std::cout << "Плотность f(x) = " << h.get_density(x) << std::endl;
			std::cout << "Мат. ожидание M[ksi] = " << h.get_expected_value() << std::endl;
			std::cout << "Дисперсия D[ksi] = " << h.get_dispersion() << std::endl;
			std::cout << "Асимметрия gamma1 = " << h.get_asymmetry() << std::endl;
			std::cout << "Эксцесс gamma2 = " << h.get_excess() << std::endl;
			std::cout << "P{x в центральном интервале} = " << h.get_P() << std::endl << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			return 0;
		}

		return 1;
	}
	case 3: {
		const std::string filename = "p.txt";

		try {
			distribution::Huber h1(1.25, 3.5, 0.8);
			std::cout << std::endl << "Original object:" << std::endl;
			std::cout << "nu = " << h1.get_nu() << std::endl;
			std::cout << "mu = " << h1.get_mu() << std::endl;
			std::cout << "lam = " << h1.get_lam() << std::endl;

			h1.save(filename);
			std::cout << "Параметры записаны в файл p.txt через метод .save(filename) объекта Huber h1()" << std::endl;

			distribution::Huber h2;
			h2.load(filename);
			std::cout << "Данные из файла p.txt записаны в объект Huber h2() через метод load; геттеры:" << std::endl;
			std::cout << "nu = " << h2.get_nu() << std::endl;
			std::cout << "mu = " << h2.get_mu() << std::endl;
			std::cout << "lam = " << h2.get_lam() << std::endl;

			distribution::Huber h3(filename);
			std::cout << "Данные из файла p.txt записаны в объект Huber h3() через конструктор Huber(filename); геттеры:" << std::endl;
			std::cout << "nu = " << h3.get_nu() << std::endl;
			std::cout << "mu = " << h3.get_mu() << std::endl;
			std::cout << "lam = " << h3.get_lam() << std::endl;

			// проверка, что характеристики совпадают для разных конструкторов объекта класса Huber
			std::cout << "Константа K и вероятность P" << std::endl;
			std::cout << std::endl << "Конструктор Huber(): k = " << h1.get_K() << ", P = " << h1.get_P() << std::endl;
			std::cout << "Конструктор Huber(double nu, double mu, double lam): k = " << h2.get_K() << ", P = " << h2.get_P() << std::endl;
			std::cout << "Конструктор Huber(const std::string& filename): k = " << h3.get_K() << ", P = " << h3.get_P() << std::endl;
		}
		catch (const std::exception& e) {
			std::cout << "Error during persistence test: " << e.what() << std::endl;
			return 0;
		}

		return 1;
	}
	case 4: {

	}
	default: {
		return 0;
	}

	}
}

int main() {
	setlocale(LC_ALL, "rus");

	srand(static_cast<unsigned int>(std::time(nullptr))); // для того, чтобы метод get_random_value() всякий раз генерировал разные числа
	bool flag = false;

	while (!flag) {
		int res = testing();
		if (res == 0) {
			flag = true;
		}
	}

	return 0;
}