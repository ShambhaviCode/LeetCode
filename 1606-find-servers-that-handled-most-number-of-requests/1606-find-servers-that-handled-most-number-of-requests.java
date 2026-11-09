import java.util.*;

class Solution {
    public List<Integer> busiestServers(
        int k, int[] arrival, int[] load
    ) {
        int n = arrival.length;

        // Available servers
        TreeSet<Integer> available = new TreeSet<>();

        for (int i = 0; i < k; i++) {
            available.add(i);
        }

        // {finishTime, serverId}
        PriorityQueue<int[]> busy = new PriorityQueue<>(
            (a, b) -> Integer.compare(a[0], b[0])
        );

        int[] count = new int[k];

        for (int i = 0; i < n; i++) {

            // Release servers that have completed requests
            while (!busy.isEmpty() &&
                   busy.peek()[0] <= arrival[i]) {
                int server = busy.poll()[1];
                available.add(server);
            }

            // Drop request if all servers are busy
            if (available.isEmpty()) {
                continue;
            }

            // Preferred server
            int target = i % k;

            // Find next available server
            Integer server = available.ceiling(target);

            // Wrap around if necessary
            if (server == null) {
                server = available.first();
            }

            available.remove(server);

            // Update request count
            count[server]++;

            // Mark server as busy
            busy.offer(new int[]{
                arrival[i] + load[i], server
            });
        }

        // Find maximum number of requests
        int max = 0;

        for (int c : count) {
            max = Math.max(max, c);
        }

        // Collect busiest servers
        List<Integer> ans = new ArrayList<>();

        for (int i = 0; i < k; i++) {
            if (count[i] == max) {
                ans.add(i);
            }
        }

        return ans;
    }
}
