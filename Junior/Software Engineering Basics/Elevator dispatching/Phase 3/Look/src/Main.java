import java.util.Scanner;

public class Main extends Test{
    @SuppressWarnings("InfiniteLoopStatement")
    public static void main(String[] args) {
        Control control = new Control();

        int[] served0 = {0, 1, 2, 3, 4, 5, 6, 7, 8};
        int[] served1 = {0, 4, 5, 6, 7, 8, 9, 10, 11};
        int[] served2 = {10, 11, 12, 13, 14, 15, 16, 17, 18};
        int[] served3 = {12, 13, 14, 15, 16, 17, 18, 19, 20};
        configure(control, 0, served0, 10, 1000, 800, 1200, 0);
        configure(control, 1, served1, 10, 1000, 800, 1200, 0);
        configure(control, 2, served2, 10, 1000, 800, 1200, 1);
        configure(control, 3, served3, 10, 1000, 800, 1200, 1);

        control.start(0);
        control.start(1);
        control.start(2);
        control.start(3);

        int floor, dest, weight;
        while (true) {
            Scanner scanner = new Scanner(System.in);
            floor = scanner.nextInt();
            dest = scanner.nextInt();
            weight = scanner.nextInt();
            addWaiting(control, floor, weight, dest);
        }
    }
}
