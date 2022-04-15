import java.awt.*;
import java.util.List;
import java.util.*;

public class Control{
    private final List<LinkedList<Passenger>> waitingUp = Collections.synchronizedList(new ArrayList<>(21));
    private final List<LinkedList<Passenger>> waitingDown = Collections.synchronizedList(new ArrayList<>(21));
    private final Elevator[] elevator = new Elevator[4];
    private final View view;

    Control() {
        for (int i=0; i<21; i++) {
            waitingUp.add(new LinkedList<>());
            waitingDown.add(new LinkedList<>());
        }

        elevator[0] = new Elevator(this, 0);
        elevator[1] = new Elevator(this, 1);
        elevator[2] = new Elevator(this, 2);
        elevator[3] = new Elevator(this, 3);

        view = new View(this);
    }

    public boolean add(int floor, Passenger passenger) {
        if (floor < 0 || floor > 20 || passenger.getDest() == floor)
            return false;

        if (passenger.getDest() > floor) {
            LinkedList<Passenger> temp = waitingUp.get(floor);
            temp.add(passenger);
            waitingUp.set(floor, temp);
        }
        else {
            LinkedList<Passenger> temp = waitingDown.get(floor);
            temp.add(passenger);
            waitingDown.set(floor, temp);
        }

        view.setStatus(floor, waitingUp.get(floor).size(), waitingDown.get(floor).size());

        return true;
    }

    public boolean isEmpty(int floor, boolean up) {
        return up ? waitingUp.get(floor).isEmpty() : waitingDown.get(floor).isEmpty();
    }

    public LinkedList<Passenger> get(int floor, int capacity, int weight, Set<Integer> servedFloors, boolean up) {
        LinkedList<Passenger> list = new LinkedList<>();

        if (up) {
            for (int i=0; i<waitingUp.get(floor).size() && capacity > 0; ) {
                Passenger p = waitingUp.get(floor).get(i);
                if (servedFloors.contains(p.getDest()) && p.getWeight() <= weight) {
                    list.add(p);
                    capacity --;
                    weight -= p.getWeight();
                    waitingUp.get(floor).remove(i);
                }
                else
                    i++;
            }
        }
        else {
            for (int i=0; i<waitingDown.get(floor).size() && capacity > 0; ) {
                Passenger p = waitingDown.get(floor).get(i);
                if (servedFloors.contains(p.getDest()) && p.getWeight() <= weight) {
                    list.add(p);
                    capacity --;
                    weight -= p.getWeight();
                    waitingDown.get(floor).remove(i);
                }
                else
                    i++;
            }
        }

        view.setStatus(floor, waitingUp.get(floor).size(), waitingDown.get(floor).size());

        return list;
    }

    public boolean setServedFloors(int elevator, Set<Integer> servedFloors) {
        return this.elevator[elevator].setServedFloors(servedFloors);
    }

    public boolean setMaxWeight(int elevator, int maxWeight) {
        return this.elevator[elevator].setMaxWeight(maxWeight);
    }

    public boolean setMaxCapacity(int elevator, int maxCapacity) {
        return this.elevator[elevator].setMaxCapacity(maxCapacity);
    }

    public boolean setMoveSpeed(int elevator, int moveSpeed) {
        return this.elevator[elevator].setMoveSpeed(moveSpeed);
    }

    public boolean setDoorSpeed(int elevator, int doorSpeed) {
        return this.elevator[elevator].setDoorSpeed(doorSpeed);
    }

    public boolean setInitialFloor(int elevator, int floor) {
        return this.elevator[elevator].setInitialFloor(floor);
    }

    public void start(int elevator) {
        (new Thread(this.elevator[elevator])).start();
    }

    public void displayServedFloors(int elevator, Set<Integer> servedFloors) {
        view.displayServedFloors(elevator, servedFloors);
    }

    public void displayElevator(int elevator, int floor, Color color) {
        view.displayElevator(elevator, floor, color);
    }
}
