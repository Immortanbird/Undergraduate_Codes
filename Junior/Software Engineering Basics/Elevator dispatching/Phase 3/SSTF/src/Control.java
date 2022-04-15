import java.awt.*;
import java.util.*;
import java.util.List;

public class Control{
    private final List<ArrayList<Passenger>> waitingUp;
    private final List<ArrayList<Passenger>> waitingDown;
    private final Elevator[] elevator;
    private final View view;

    Control() {
        waitingUp = Collections.synchronizedList(new ArrayList<>(21));
        waitingDown = Collections.synchronizedList(new ArrayList<>(21));
        for (int i=0; i<21; i++) {
            waitingUp.add(new ArrayList<>());
            waitingDown.add(new ArrayList<>());
        }

        elevator= new Elevator[4];
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
            waitingUp.get(floor).add(passenger);
        }
        else {
            waitingDown.get(floor).add(passenger);
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
            for (int i=0; i<waitingUp.get(floor).size() && capacity > 0;) {
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
            for (int i=0; i<waitingDown.get(floor).size() && capacity > 0; i++) {
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

    public int getDest(int serial, int floor, Set<Integer> servedFloors, boolean up) {
        // Finds proper elevator for request in floor
        // Proper Elevator: Elevator nearest to the request floor
        int MinDistance = 40;
        int index = 0;
        int step = up ? 1 : -1;

        for (int i = floor + step; i >= 0 && i < 21; i += step) {
            if (servedFloors.contains(i) && (!waitingUp.get(i).isEmpty() || !waitingDown.get(i).isEmpty())) {
                for(int j = 0; j < elevator.length; j++) {
                    int distancei = Math.abs(floor - i);
                    if(distancei <= MinDistance) {
                        MinDistance = distancei;
                        index = j;
                    }
                }
                return i;
            }
        }

        step = -step;
        for (int i = floor + step; i >= 0 && i < 21; i += step) {
            if (servedFloors.contains(i) && (!waitingUp.get(i).isEmpty() || !waitingDown.get(i).isEmpty())) {
                for(int j = 0; j < elevator.length; j++) {
                    int distancei = Math.abs(floor - i);
                    if(distancei <= MinDistance) {
                        MinDistance = distancei;
                        index = j;
                    }
                }
                return i;
            }
        }
        if(index != serial) {
            return -1;
        }
        return -1;
    }

    public void displayServedFloors(int elevator, Set<Integer> servedFloors) {
        view.displayServedFloors(elevator, servedFloors);
    }
    
    public void displayElevator(int elevator, int floor, Color color) {
        view.displayElevator(elevator, floor, color);
    }
}
