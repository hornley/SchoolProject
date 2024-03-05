package symboliclogiccalculator;

import java.io.*;
import java.util.*;

public class SymbolicLogicCalculator {
    public static HashMap<String, ArrayList<Boolean>> propositions = new HashMap<>();
    public static String[] logicalConnectives = {"A", "V", "O", "->", "<->", "==", "~"};
    public static Set<Character> variables = new HashSet<>();
    
    public class Proposition {
        public String proposition;
        private ArrayList<Boolean> truthValues;
        private Proposition left;
        private Proposition right;
        private String logicalConnective;
        private boolean isSimple;
        
        
        public Proposition(String input, boolean simple, String LC) {
            proposition = input;
            isSimple = simple;
            logicalConnective = LC;
        }
        
        public ArrayList<Boolean> getTruthValues() {
            return truthValues;
        }
        
        public void setLeftRight(Proposition left, Proposition right) {
            this.left = left;
            this.right = right;
        }
    }
    
    public static String removeParenthesis(String input) {
        if (input.contains("(") && input.contains(")") && input.startsWith("(")) return input.substring(1, input.length()-1);
        return input;
    }
    
    public static boolean isProposition(String input) {
        for (String LC : logicalConnectives) {
            if (input.contains(LC)) return true;
        }
        return false;
    }
    
    public static ArrayList<String> getLeftRightProposition(String input) {
        ArrayList<String> proposition = new ArrayList<>();
        
        for (int to = 0; to <input.length(); to++) {
            for (String LC : logicalConnectives) {
                if (LC.equals("~")) continue;
                if (input.substring(to, to+1).equals(LC)) {
                    proposition.add(input.substring(0, to));
                    proposition.add(removeParenthesis(input.substring(to+1, input.length())));
                    proposition.add(LC);
                    break;
                }
            }
            if (input.contains("->") || input.contains("<->")) {
                if (input.substring(to, to+2).equals("->")) {
                    proposition.add(input.substring(0, to));
                    proposition.add(removeParenthesis(input.substring(to+2, input.length())));
                    proposition.add("->");
                }
                if (input.substring(to, to+3).equals("<->")) {
                    proposition.add(input.substring(0, to));
                    proposition.add(removeParenthesis(input.substring(to+3, input.length())));
                    proposition.add("<->");
                }
            }
            if (!proposition.isEmpty()) break;
        }
        System.out.println(proposition);
        return proposition;
    }
    
    public static void checkPropositions(String input) {
        solveTruthValues(input);
    }
    
    public static ArrayList<Boolean> negation(ArrayList<Boolean> truthValues) {
        ArrayList<Boolean> TruthValues = new ArrayList<>();
        for (int x = 0; x < truthValues.size(); x++) {
            TruthValues.add(!truthValues.get(x));
        }
        return TruthValues;
    }
    
    public static ArrayList<Boolean> solveTruthValues(String proposition) {
        if (propositions.get(proposition) != null) return propositions.get(proposition);
        proposition = proposition.replaceAll("\\s+","");
        ArrayList<Boolean> TruthValues = new ArrayList<>();
        ArrayList<Boolean> leftTruthValues = new ArrayList<>();
        ArrayList<Boolean> rightTruthValues = new ArrayList<>();
        String leftProposition = "";
        String rightProposition = "";
        String logicalConnective = "";
        
        if (proposition.startsWith("~(") && proposition.endsWith(")")) {
            ArrayList<Boolean> x = new ArrayList<>();
            if (propositions.get(proposition.substring(2, proposition.length())) != null) x = propositions.get(proposition.substring(2, proposition.length()-1));
            else x = solveTruthValues(proposition.substring(2, proposition.length()-1));
            propositions.put(proposition, negation(x));
            return negation(x);
        }
        
        if (variables.size() == 2 && proposition.startsWith("(") && proposition.contains(")")) {
            proposition = proposition.replace("(", "");
            proposition = proposition.replace(")", "");
        }
        
        if (proposition.startsWith("(")) {
            int right = proposition.indexOf(")");
            leftProposition = proposition.substring(1, right);
            if (proposition.length() == 5) {
                leftProposition = proposition.substring(1, 2);
                logicalConnective = proposition.substring(2, 3);
                rightProposition = proposition.substring(3, 4);
            } else {
                logicalConnective = proposition.substring(right+1, proposition.length());
                for (int to = 0; to < logicalConnective.length(); to++) {
                    for (String LC : logicalConnectives) {
                        if (logicalConnective.substring(to, to+1).equals(LC)) {
                            rightProposition = logicalConnective.substring(to+1, logicalConnective.length());
                            logicalConnective = LC;
                            break;
                        }
                    }
                    if (logicalConnective.contains("->") || logicalConnective.contains("<->")) {
                        if (logicalConnective.substring(to, to+2).equals("->")) {
                            rightProposition = logicalConnective.substring(to+2, logicalConnective.length());
                            logicalConnective = "->";
                            break;
                        }
                        if (logicalConnective.substring(to, to+3).equals("<->")) {
                            rightProposition = logicalConnective.substring(to+3, logicalConnective.length());
                            logicalConnective = "<->";
                            break;
                        }
                    }
                    if (rightProposition != "") break;
                }
            } // (aVb)Ac
        } else {
            leftProposition = getLeftRightProposition(proposition).get(0);
            rightProposition = getLeftRightProposition(proposition).get(1);
            logicalConnective = getLeftRightProposition(proposition).get(2);
        }
        
        if (rightProposition.contains("~") && rightProposition.length() == 2) {
            propositions.put(rightProposition, negation(propositions.get(rightProposition.substring(1, 2))));
        }
        
        if (leftProposition.contains("~") && leftProposition.length() == 2) {
            propositions.put(leftProposition, negation(propositions.get(leftProposition.substring(1, 2))));
        }
        
        if (propositions.keySet().contains(leftProposition) && propositions.keySet().contains(rightProposition)) {
            leftTruthValues = propositions.get(leftProposition);
            rightTruthValues = propositions.get(rightProposition);
        }
        
        if (!propositions.keySet().contains(leftProposition)) {
            leftTruthValues = solveTruthValues(leftProposition);
            rightTruthValues = propositions.get(rightProposition);
        }
        
        if (!propositions.keySet().contains(rightProposition)) {
            leftTruthValues = propositions.get(leftProposition);
            rightTruthValues = solveTruthValues(rightProposition);
        }
        
        switch (logicalConnective) {
            case "A":
                for (int x = 0; x < leftTruthValues.size(); x++) {
                    boolean truthValue = leftTruthValues.get(x) && rightTruthValues.get(x);
                    TruthValues.add(truthValue);
                }   break;
            case "V":
                for (int x = 0; x < leftTruthValues.size(); x++) {
                    boolean truthValue = leftTruthValues.get(x) || rightTruthValues.get(x);
                    TruthValues.add(truthValue);
                }   break;
            case "O":
                for (int x = 0; x < leftTruthValues.size(); x++) {
                    boolean truthValue = leftTruthValues.get(x) ^ rightTruthValues.get(x);
                    TruthValues.add(truthValue);
                }   break;
            case "->":
                for (int x = 0; x < leftTruthValues.size(); x++) {
                    boolean truthValue = true;
                    if (leftTruthValues.get(x) && !rightTruthValues.get(x)) truthValue = false;
                    TruthValues.add(truthValue);
                }   break;
            case "<->":
                for (int x = 0; x < leftTruthValues.size(); x++) {
                    boolean truthValue = leftTruthValues.get(x) ^ rightTruthValues.get(x);
                    TruthValues.add(!truthValue);
                }   break;
            default:
                break;
        }
        
//        System.out.println(proposition + " = " + leftTruthValues + " " + logicalConnective + " " + rightTruthValues + " = " + TruthValues);
        
        propositions.put(proposition, TruthValues);
        
        return TruthValues;
    }
    
    public static ArrayList<Boolean> initializeTruthTable(int rows, int vn, int cn) {
        ArrayList<Boolean> arr = new ArrayList<>();
        for (int row = 0; row < rows; row++) {
            if (Math.ceil((row + 1)/Math.pow(2, vn - cn)) % 2 == 1) arr.add(row, true);
            else arr.add(row, false);
        }
        return arr;
    }
    
    public static char getVariableFromSet(int index) {
        int x = 0;
        char z = 'a';
        for (char variable : variables) {
            if (x == index) {
                z =  variable;
            }
            x++;
        }
        return z;
    }
    
    public static void main(String[] args) {
        BufferedReader dataIn = new BufferedReader( new InputStreamReader(System.in) );
        String input = "";
        
        int variableNumbers = 0;
        int numberOfRows = 0;
        
        try {
            System.out.print("Proposition: ");
            input = dataIn.readLine();
            for (char x = 'a'; x <= 'z'; x++) {
                for (int y = 0; y < input.length(); y++) {
                    if (input.charAt(y) == x) {
                        variables.add(x);
                    }
                }
            }
            variableNumbers = variables.size();
            numberOfRows = (int)Math.pow(2, variableNumbers);
        } catch ( IOException e ) {
            System.out.println("Error Occured!");
        }

        for (int vn = 0; vn < variableNumbers; vn++) {
            propositions.put(Character.toString(getVariableFromSet(vn)), initializeTruthTable(numberOfRows, variableNumbers, vn + 1));
        }
        
        for (char variable : variables) {
            ArrayList x = propositions.get(Character.toString(variable));
        }
        
        checkPropositions(input);
        
        for (String proposition : propositions.keySet()) {
            System.out.println(proposition + " = " + propositions.get(proposition));
        }
    }
}