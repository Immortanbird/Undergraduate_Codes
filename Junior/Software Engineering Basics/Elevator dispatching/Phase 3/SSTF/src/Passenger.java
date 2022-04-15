public class Passenger {
    private final int weight;
    private final int dest;

    Passenger(int weight, int dest) {
        this.weight = weight;
        this.dest = dest;
    }

    public int getWeight() {
        return weight;
    }

    public int getDest() {
        return dest;
    }
}