import java.io.IOException;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;

public class MergeSort {
    final static int LEN = 100000;

    public static void main(String[] args) throws IOException {
        long start = System.currentTimeMillis();

        int[] nums = new int[LEN];

        Scanner scanner = new Scanner(Paths.get("D:\\Codes\\Compiling Principle\\Lab.1.Learning Programing Language\\test.txt"), "UTF-8");

        for (int i=0; i<nums.length && scanner.hasNextInt(); i++)
            nums[i] = scanner.nextInt();

        sort(nums);

        System.out.println("Sorted(ascending):");
        System.out.println(Arrays.toString(nums));

        long end = System.currentTimeMillis();

        System.out.println("Timecost: " + (end - start) + "ms");
    }

    public static void sort(int[] nums) {
        int[] temp = new int[nums.length];
        sort(nums, 0, nums.length - 1, temp);
    }

    private static void sort(int[] nums, int left, int right, int[] temp) {
        if (left >= right)
            return;

        int mid = (left + right) / 2;
        sort(nums, left, mid, temp);
        sort(nums, mid + 1, right, temp);

        int i = left;
        int j = mid + 1;
        int k = left;

        while (i <= mid && j<= right) {
            if (nums[i] < nums[j])
                temp[k++] = nums[i++];
            else
                temp[k++] = nums[j++];
        }

        while (i <= mid)
            temp[k++] = nums[i++];

        while (j <= right)
            temp[k++] = nums[j++];

        for (i=left; i <= right; i++)
            nums[i] = temp[i];
    }
}