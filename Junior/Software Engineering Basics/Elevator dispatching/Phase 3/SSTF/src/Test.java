import java.util.HashSet;
import java.util.Set;

public abstract class Test {
    public static boolean addWaiting(Control control, int floor, int weight, int dest) {
        if (floor == -1)
            floor ++;

        Passenger passenger = new Passenger(weight, dest);

        return control.add(floor, passenger);
    }

    public static boolean configure(Control control, int elevator, int[] servedFloors, int maxCapacity, int maxWeight, int doorSpeed, int moveSpeed, int initialFloor) {
        Set<Integer> hashServedFloors = new HashSet<>();
        for (int x : servedFloors)
            hashServedFloors.add(x);

        if (!control.setServedFloors(elevator, hashServedFloors))
            return false;
        if (!control.setMaxCapacity(elevator, maxCapacity))
            return false;
        if (!control.setMaxWeight(elevator, maxWeight))
            return false;
        if (!control.setDoorSpeed(elevator, doorSpeed))
            return false;
        if (!control.setMoveSpeed(elevator, moveSpeed))
            return false;
        if (!control.setInitialFloor(elevator, initialFloor))
            return false;

        return true;
    }
}