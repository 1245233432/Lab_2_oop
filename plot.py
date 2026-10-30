import sys
import numpy as np
import matplotlib.pyplot as plt
from math import erf, sqrt, exp, pi


def phi(t):
    return exp(-0.5 * t * t) / sqrt(2.0 * pi)


def Phi(t):
    return 0.5 * (1.0 + erf(t / sqrt(2.0)))


def K(nu):
    return (2.0 / nu) * phi(nu) + 2.0 * Phi(nu) - 1.0


def huber_density(x, nu, mu, lam):
    z = (x - mu) / lam
    c = 1.0 / (K(nu) * lam * sqrt(2.0 * pi))
    if abs(z) <= nu:
        return c * exp(-0.5 * z * z)
    return c * exp(0.5 * nu * nu - nu * abs(z))


def main():
    if len(sys.argv) < 5:
        print("Usage: python plot.py x nu mu lam")
        sys.exit(1)

    x_mark = float(sys.argv[1])
    nu     = float(sys.argv[2])
    mu     = float(sys.argv[3])
    lam    = float(sys.argv[4])

    left  = mu - 6.0 * lam
    right = mu + 6.0 * lam
    xs = np.linspace(left, right, 600)
    ys = [huber_density(xi, nu, mu, lam) for xi in xs]

    y_mark = huber_density(x_mark, nu, mu, lam)

    plt.figure(figsize=(9, 5))
    plt.plot(xs, ys, color="blue", linewidth=2,
             label=f"Huber  ν={nu}, μ={mu}, λ={lam}")
    plt.scatter([x_mark], [y_mark], color="red", zorder=5, s=50,
                label=f"f({x_mark:g}) = {y_mark:.5f}")

    plt.title(f"Плотность распределения Хьюбера\nν = {nu}, μ = {mu}, λ = {lam}")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.legend()
    plt.grid(True, alpha=0.4)
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()