import java.util.*;

/* usage: javac r222.java && java r222 >db.txt */
public class r222 {
    private final static String SOLVED = "RRRRYYYYBBBBOOOOWWWWGGGG";

    private final static int op0[] = {1,3,0,2,21,20,6,7,4,5,10,11,12,13,14,15,9,8,18,19,16,17,22,23};
    private final static int op1[] = {0,1,8,10,5,7,4,6,15,9,14,11,12,13,20,22,16,17,18,19,3,21,2,23};
    private final static int op2[] = {0,19,2,17,4,1,6,3,9,11,8,10,12,7,14,5,16,13,18,15,20,21,22,23};

    private static String update(String cfg, int op) {
        char new_cfg[] = new char[24];
        int targets[] = op == 0 ? op0 : (op == 1 ? op1 : op2);

        for (int i=0; i<24; i++)
            new_cfg[i] = cfg.charAt(targets[i]);

        return new String(new_cfg);
    }

    private static void makeDB() {
        Map<String, String> tree = new HashMap<String, String>();
        Map<String, String> tmp_tree = new HashMap<String, String>();

        tree.put(SOLVED, "");
        tmp_tree.put(SOLVED, "");

        while (tmp_tree.size() > 0) {
            Map<String, String> new_tree = new HashMap<String, String>();

            for (Map.Entry<String,String> entry : tmp_tree.entrySet()) {
                String cfg = entry.getKey();
                String ops = entry.getValue();

                for (int op=0; op<3; op++) {
                    String new_cfg = update(cfg, op);
                    if (!tree.containsKey(new_cfg)) {
                        tree.put(new_cfg, ops + op);
                        new_tree.put(new_cfg, ops + op);
                    }
                }
            }

            tmp_tree = new_tree;
        }

        for (Map.Entry<String,String> entry : tree.entrySet())
            System.out.println(entry.getKey() + ": '" + entry.getValue() + "'");
    }

    public static void main(String[] args) {
        makeDB();
    }
}
