import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        if (args[0].equals("")) {
            System.out.println("Need parameter.");
            return;
        }

        FileWriter writer = new FileWriter("out.txt", false);
        writer.write("");
        writer.flush();
        writer.close();
        MyScanner scanner = new MyScanner(new FileReader(args[0]));
        System.out.println("Start...");
        scanner.scan();
        System.out.println("Finish...");
    }
}
