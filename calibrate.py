import numpy as np
import matplotlib.pyplot as plt

x = np.array([0.02, 0.33, 0.46, 0.61, 0.73, 0.86, 0.98])
t = np.array([0.0, 0.1, 0.2, 0.4, 0.6, 0.8, 1.0])

N = len(x)

def y(x, w):
    x = np.asarray(x)
    powers = np.arange(len(w))
    return np.sum((x[..., None] ** powers) * w, axis=-1)


def least_squares(x, t, w):
    return 0.5 * np.sum((y(x, w) - t) ** 2)


for M in [2, 3, 4, 5]:
    X = np.vander(x, M + 1, increasing=True)

    # Solve normal equations: (X^T X) w = X^T t
    w = np.linalg.solve(X.T @ X, X.T @ t)

    print(f"Least squares (M={M}): {least_squares(x, t, w):.6f}")

    # Plot
    p_x = np.linspace(0, 1, 200)

    plt.figure()
    plt.plot(x, t, 'ob', label="Training data")
    plt.plot(p_x, y(p_x, w), 'r', linewidth=2, label=f"Polynomial M={M}")

    plt.xlim(-0.04, 1.04)
    plt.ylim(-0.04, 1.04)
    plt.legend()
    plt.title(f"Polynomial Fit (Degree {M})")
    plt.show()
