import java.awt.*;
import java.util.*;
import java.util.List;

public class Elevator implements Runnable{
    private final Control control;

    private final int serial;

    private boolean up;
    private int maxWeight;
    private int maxCapacity;
    private int moveSpeed;
    private int doorSpeed;
    private int currentCount = 0;
    private int currentWeight = 0;
    private int currentFloor;
    private int destFloor;

    public static final int STATUS_UP = 1;
    public static final int STATUS_DOWN = -1;
    public static final int STATUS_IDEL = 0;

    private final List<Integer> servedFloors;
    private final Map<Integer, Integer> weight;
    private final Map<Integer, Integer> count;

    Elevator(Control control, int serial) {
        super();
        this.control = control;
        this.serial = serial;

        weight = new HashMap<>();
        count = new HashMap<>();

        servedFloors = Collections.synchronizedList(new ArrayList<>());
    }

    public boolean setMaxWeight(int maxWeight) {
        if (maxWeight > 0) {
            this.maxWeight = maxWeight;
            return true;
        }

        return false;
    }

    public boolean setMaxCapacity(int maxCapacity) {
        if (maxCapacity > 0) {
            this.maxCapacity = maxCapacity;
            return true;
        }
        else
            return false;
    }

    public boolean setMoveSpeed(int moveSpeed) {
        if (moveSpeed > 0) {
            this.moveSpeed = moveSpeed;
            return true;
        }

        return false;
    }

    public boolean setDoorSpeed(int doorSpeed) {
        if (doorSpeed > 0) {
            this.doorSpeed = doorSpeed;
            return true;
        }

        return false;
    }

    public boolean setInitialFloor(int floor) {
        if (floor < 0 || floor > 20)
            return false;

        destFloor = currentFloor = floor;

        control.displayElevator(serial, currentFloor, Color.GREEN);

        return true;
    }

    public boolean setServedFloors(Set<Integer> servedFloors) {
        this.servedFloors.clear();
        for (int i : servedFloors) {
            if (i >=0 && i <= 20 && !this.servedFloors.contains(i))
                this.servedFloors.add(i);
            else
                return false;
        }
        Collections.sort(this.servedFloors);

        control.displayServedFloors(serial, servedFloors);

        return true;
    }

    @Override
    @SuppressWarnings("InfiniteLoopStatement")
    public void run() {
        while (true) {
            // Decide
                int dest = control.getDest(serial, currentFloor, new HashSet<>(servedFloors), up);
                if (dest != -1)
                    System.out.println(serial + " get dest " + dest);

                if (dest == -1) { // No waiting in served floors
                    int step = up ? 1 : -1;

                    for (int i = currentFloor + step; i >= 0 && i < 21; i += step) {
                        if (servedFloors.contains(i) && count.containsKey(i)) {
                            dest = i;
                            break;
                        }
                    }

                    if (dest == -1) {
                        up = !up;
                        step = -step;
                        for (int i = currentFloor + step; i >= 0 && i < 21; i += step) {
                            if (servedFloors.contains(i) && count.containsKey(i)) {
                                dest = i;
                                break;
                            }
                        }
                    }

                    if (dest == -1) {
                        dest = currentFloor;
                    }
                }
                else if (up ^ dest < currentFloor){
                    int nearest = -1;
                    int step = up ? 1 : -1;

                    for (int i = currentFloor + step; i >= 0 && i < 21; i += step) {
                        if (servedFloors.contains(i) && count.containsKey(i)) {
                            nearest = i;
                            break;
                        }
                    }

                    if (nearest != -1) {
                        dest = up ? Math.min(nearest, dest) : Math.max(nearest, dest);
                    }
                }
                else {
                    int nearest = -1;
                    int step = up ? 1 : -1;

                    for (int i = currentFloor + step; i >= 0 && i < 21; i += step) {
                        if (servedFloors.contains(i) && count.containsKey(i)) {
                            nearest = i;
                            break;
                        }
                    }

                    if (nearest != -1) {
                        dest = nearest;
                    }
                }

                // Sum of people that get in and out
                int sum = 0;

                // Get out
                if (count.containsKey(currentFloor)) {
                    sum += count.get(currentFloor);
                    currentCount -= count.get(currentFloor);
                    currentWeight -= weight.get(currentFloor);
                    count.remove(currentFloor);
                    weight.remove(currentFloor);
                }

                // Get in
                if (!control.isEmpty(currentFloor, up)) {
                    LinkedList<Passenger> list = control.get(currentFloor, maxCapacity - currentCount, maxWeight - currentWeight, new HashSet<>(servedFloors), up);
                    sum += list.size();
                    while (!list.isEmpty()) {
                        Passenger p = list.poll();
                        currentCount ++;
                        currentWeight += p.getWeight();
                        count.put(p.getDest(), count.getOrDefault(p.getDest(), 0) + 1);
                        weight.put(p.getDest(), weight.getOrDefault(p.getDest(), 0) + p.getWeight());
                    }
                }

                // Passenger loading time cost
                // Assuming that each passenger need 1s to get in or out
                if (sum > 0) {
                    control.displayElevator(serial, currentFloor, Color.RED);
                    try {
                        Thread.sleep((long)sum * 1000 + 2L * doorSpeed);
                    }catch (InterruptedException exception) {
                        exception.printStackTrace();
                    }
                    control.displayElevator(serial, currentFloor, Color.GREEN);
                }

                // Elevator moving
                if (dest != currentFloor) {
                    if (destFloor != currentFloor)
                        destFloor = up ? Math.min(dest, destFloor) : Math.max(dest, destFloor);
                    else
                        destFloor = dest;
                }

                if (destFloor != currentFloor) {
                    up = destFloor > currentFloor;

                    try {
                        Thread.sleep(moveSpeed);
                    } catch (InterruptedException exception) {
                        exception.printStackTrace();
                    }

                    if (servedFloors.contains(currentFloor))
                        control.displayElevator(serial, currentFloor, Color.GRAY);
                    else
                        control.displayElevator(serial, currentFloor, Color.BLACK);
                    currentFloor += up ? 1 : -1;
                    control.displayElevator(serial, currentFloor, Color.GREEN);
                }
            }
    }
}
