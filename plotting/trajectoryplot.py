# pandas for csv handling and matplot for plotting
import pandas as pd
import matplotlib.pyplot as plt

# store csv
CSV_PATH = "../data/trajectory.csv"

# loads trajectory from given path.
def load_trajectory(path):
    print(f"Loading trajectory from: {path}")
    df = pd.read_csv(path)
    return df

# set up the graph
def plot_basic(df):
    plt.figure()
    plt.plot(df["x"], df["y"])
    plt.xlabel("X Position (m)")
    plt.ylabel("Y Position (m)")
    plt.title("Bullet Trajectory (No Drag)")
    plt.grid(True)
    plt.show()

# colored scatter plot
def plot_colored(df):
    plt.figure()
    scatter = plt.scatter(df["x"], df["y"], c=df["time"])
    plt.colorbar(scatter, label="Time (s)")
    plt.xlabel("X Position (m)")
    plt.ylabel("Y Position (m)")
    plt.title("Trajectory Colored by Time")
    plt.grid(True)
    plt.show()

# main
def main():
    # store loaded trajectory
    df = load_trajectory(CSV_PATH)

    # standard trajectory line
    plot_basic(df)

    # colored scatter by time
    plot_colored(df)


if __name__ == "__main__":
    main()
