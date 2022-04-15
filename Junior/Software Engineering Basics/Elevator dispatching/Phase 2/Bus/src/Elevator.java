import java.awt.*;
import java.util.List;
import java.util.*;

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

    private final List<Integer> servedFloors;
    private final Map<Integer, Integer> weight;
    private final Map<Integer, Integer> count;

    Elevator(Control control, int serial) {
        this.control = control;
        this.serial = serial;

        up = true;
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
        if (!servedFloors.contains(floor))
            return false;

        currentFloor = floor;

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
            // Decide elevator direction and next destination floor
            int destFloor;
            if (up) {
                if (servedFloors.indexOf(currentFloor) + 1 < servedFloors.size())
                    destFloor = servedFloors.get(servedFloors.indexOf(currentFloor) + 1);
                else {
                    up = false;
                    destFloor = servedFloors.get(servedFloors.indexOf(currentFloor) - 1);
                }
            }
            else {
                if (servedFloors.indexOf(currentFloor) > 0)
                    destFloor = servedFloors.get(servedFloors.indexOf(currentFloor) - 1);
                else {
                    up = true;
                    destFloor = servedFloors.get(servedFloors.indexOf(currentFloor) + 1);
                }
            }
            int distance = Math.abs(destFloor - currentFloor);

            // Passengers get out and then in
            if (!control.isEmpty(currentFloor, up) || count.containsKey(currentFloor)) {
                control.displayElevator(serial, currentFloor, Color.RED);
                // The number of people that get in and out
                int sum = 0;

                //Get out
                if (count.containsKey(currentFloor)) {
                    sum += count.get(currentFloor);
                    currentCount -= count.remove(currentFloor);
                    currentWeight -= weight.remove(currentFloor);
                }

                //Get in
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

                // Simulate time cost
                // Assume that each person needs 0.5s to get in or out
                if (sum > 0) {
                    control.displayElevator(serial, currentFloor, Color.RED);
                    try {
                        Thread.sleep((long) sum * 500);
                    } catch (InterruptedException exception) {
                        exception.printStackTrace();
                    }
                    control.displayElevator(serial, currentFloor, Color.GREEN);
                }
            }

            //Elevator moving
            while (distance-- > 0) {
                try {
                    Thread.sleep(moveSpeed);
                }catch (InterruptedException exception) {
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