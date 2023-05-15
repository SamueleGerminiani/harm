import sys

import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

#X = np.random.random((100, 100)) # sample 2D array
X = np.loadtxt(sys.argv[1])


plt.imshow(X, cmap="gray")
plt.show()
