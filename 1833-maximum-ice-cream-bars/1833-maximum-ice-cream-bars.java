class Solution {
    public int maxIceCream(int[] costs, int coins) {
        int maxCost = 0;

        for (int cost : costs) {
            maxCost = Math.max(maxCost, cost);
        }

        int[] count = new int[maxCost + 1];

        for (int cost : costs) {
            count[cost]++;
        }

        int bars = 0;

        for (int price = 1; price <= maxCost; price++) {
            if (count[price] == 0) continue;

            long totalCost = (long) price * count[price];

            if (coins >= totalCost) {
                bars += count[price];
                coins -= totalCost;
            } else {
                bars += coins / price;
                break;
            }
        }

        return bars;
    }
}