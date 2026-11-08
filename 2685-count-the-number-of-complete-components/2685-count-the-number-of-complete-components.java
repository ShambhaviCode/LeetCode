import java.util.*;

class Solution {
    public int countCompleteComponents(int n, int[][] edges) {
        List<Integer>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }

        for (int[] e : edges) {
            graph[e[0]].add(e[1]);
            graph[e[1]].add(e[0]);
        }

        boolean[] visited = new boolean[n];
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                List<Integer> component = new ArrayList<>();
                dfs(i, graph, visited, component);

                int vertices = component.size();
                int degreeSum = 0;

                for (int node : component) {
                    degreeSum += graph[node].size();
                }

                int edgeCount = degreeSum / 2;

                if (edgeCount == vertices * (vertices - 1) / 2) {
                    ans++;
                }
            }
        }

        return ans;
    }

    private void dfs(int node, List<Integer>[] graph, boolean[] visited, List<Integer> component) {
        visited[node] = true;
        component.add(node);

        for (int nei : graph[node]) {
            if (!visited[nei]) {
                dfs(nei, graph, visited, component);
            }
        }
    }
}