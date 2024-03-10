import java.util.*;
import javax.swing.JOptionPane;

public class SymbolicLogicCalculator {
    public static LinkedHashMap<String, ArrayList<Boolean>> propositions = new LinkedHashMap<>();
    public static String[] logicalConnectives = {"A", "V", "O", "->", "<->", "==", "~"};
    public static Set<Character> variables = new HashSet<>();
    public static String CompoundProposition = "";
    public static String CompoundPropositionLeft = "";
    public static String CompoundPropositionRight = "";
    public static String CompoundPropositionLC = "";
    public static Integer NegateCompoundProposition = 0;
    
    public static void removeDuplicates() {
        LinkedHashMap<String, ArrayList<Boolean>> temp = new LinkedHashMap<>();
        for (String p : propositions.keySet()) {
            if (p.startsWith("(") && p.endsWith(")")) {
                if (propositions.keySet().contains(p.substring(1, p.length()-1))) {
                    temp.put(p.substring(1, p.length()-1), propositions.get(p.substring(1, p.length()-1)));
                }
            } else {
                temp.put(p, propositions.get(p));
            }
        }
        propositions = temp;
    }
    
    public static boolean isValid(String input) {
        int POcount = 0;
        for (int y = 0; y < input.length(); y++) {
            if (input.substring(y, y+1).equals("(")) POcount++;
            else if (input.substring(y, y+1).equals(")")) POcount--;
        }
        return POcount == 0;
    }
    
    public static boolean checkIfCompoundNegated(String input) {
        int POcount = 0;
        if (input.startsWith("~(")) {
            POcount++;
            for (int y = 2; y < input.length(); y++) {
                if (input.substring(y, y+1).equals("(")) POcount++;
                else if (input.substring(y, y+1).equals(")")) POcount--;
                if (POcount == 0 && y != input.length()-1) return false;
            }
        }
        // If input is a negated compound proposition such as ~(((sAp)->(qVr))V(rVw))
        NegateCompoundProposition++;
        return true;
    }
    
    public static void isCompoundPropositionNegated(String input) {
        int POcount = 0;
        boolean done = false;
        String Compounded = input;
        
        if (input.startsWith("~(")) {
            if (checkIfCompoundNegated(Compounded)) {
                Compounded = Compounded.substring(2, Compounded.length()-1);
                isCompoundPropositionNegated(Compounded);
                return;
            }
        }
        
        CompoundProposition = Compounded;
        
        for (int y = 0; y < input.length(); y++ ) {
            if (done) break;
            if (Compounded.substring(y, y+1).equals("(")) POcount++;
            else if (Compounded.substring(y, y+1).equals(")")) POcount--;
            for (String LC : logicalConnectives) {
                int from = y;
                if (POcount > 0 || LC.equals("~")) continue;
                if (input.substring(y, y+1).equals(LC)) {
                    CompoundPropositionLeft = input.substring(0, y);
                    CompoundPropositionRight = input.substring(y+1, input.length());
                    CompoundPropositionLC = input.substring(y, y+1);
                    done = true;
                    break;
                }
                if (input.substring(from).contains("->") || input.substring(from).contains("<->")) {
                    if (input.substring(from, y+2).equals("->") || input.substring(from, y+2).equals("==")) {
                        CompoundPropositionLeft = input.substring(0, y);
                        CompoundPropositionRight = input.substring(y+2, input.length());
                        CompoundPropositionLC = input.substring(y, y+2);
                        done = true;
                        break;
                    } else if (input.substring(from, y+3).equals("<->")) {
                        CompoundPropositionLeft = input.substring(0, y);
                        CompoundPropositionRight = input.substring(y+3, input.length());
                        CompoundPropositionLC = input.substring(y, y+3);
                        done = true;
                        break;
                    }
                }
            }
        }
    }
    
    public static void getSimplePropositions(String input) {
        input = input.replaceAll("\\s+","");
        ArrayList<String> proposition = new ArrayList<>();
        int POcount = 0;
        HashMap<Integer, Integer> tempProposition = new HashMap<>();
        
        if (input.startsWith("(") && input.endsWith(")") && !input.equals(CompoundProposition)) input = input.substring(1, input.length()-1);
        if (input.length() == 2) return;
        
        for (int y = 0; y < input.length(); y++) {
            if (input.substring(y, y+1).equals("(")) {
                POcount++;
                if (y > 0 && input.substring(y-1, y).equals("~")) {
                    tempProposition.put(POcount, y-1);
                } else tempProposition.put(POcount, y);
            } else if (input.substring(y, y+1).equals(")")) {
                int from = tempProposition.get(POcount);
                int to = y;
                if (input.substring(from, from+1).equals("~")) proposition.add(input.substring(from+2, to));
                proposition.add(input.substring(from, to+1));
                POcount--;
            } else if (input.substring(y, y+1).equals("~") && !input.substring(y+1, y+2).equals("(") && input.length() != 4) {
                if (input.contains("->") || input.contains("<->")) {
                    if (input.substring(y, y+2).equals("->") || input.substring(y, y+2).equals("==")) {
                        proposition.add(input.substring(y, y+3));
                        proposition.add(input.substring(y+2, y+5));
                    } else if (input.substring(y, y+3).equals("<->")) {
                        proposition.add(input.substring(y, y+4));
                        proposition.add(input.substring(y+3, y+6));
                    }
                } else {
                    proposition.add(input.substring(y, y+2));
                    if (getVariablesOfProposition(input.substring(y+1, y+4)) != 1) proposition.add(input.substring(y+1, y+4));
                }
            }
        }
        
        for (String p : proposition) {
            if (!propositions.keySet().contains(p)) {
                propositions.put(p, solveTruthValues(p));
            }
        }
    }
    
    public static ArrayList<String> getLeftRightProposition(String input) {
        ArrayList<String> proposition = new ArrayList<>();
        int x = 0;
        int POcount = 0;
        
        for (int to = 0; to <input.length(); to++) {
            for (String LC : logicalConnectives) {
                if (LC.equals("~")) continue;
                if (input.substring(to, to+1).equals(LC)) {
                    if (to > 1 && variables.contains(input.charAt(to-1)) && input.substring(to-2,to-1).equals("~")) x +=1;
                    else x = 0;
                    proposition.add(input.substring(to-1-x, to));
                    proposition.add(input.substring(to+1, input.length()));
                    proposition.add(LC);
                    break;
                }
            }
            if (input.contains("->") || input.contains("<->")) {
                if (input.substring(to, to+2).equals("->")) {
                    proposition.add(input.substring(to-1-x, to));
                    proposition.add(input.substring(to+2, input.length()));
                    proposition.add("->");
                }
                if (input.substring(to, to+3).equals("<->")) {
                    proposition.add(input.substring(to-1-x, to));
                    proposition.add(input.substring(to+3, input.length()));
                    proposition.add("<->");
                }
            }
            if (!proposition.isEmpty()) break;
        }
        return proposition;
    }
    
    public static ArrayList<Boolean> negation(ArrayList<Boolean> truthValues) {
        ArrayList<Boolean> TruthValues = new ArrayList<>();
        for (int x = 0; x < truthValues.size(); x++) {
            TruthValues.add(!truthValues.get(x));
        }
        return TruthValues;
    }
    
    public static int getVariablesOfProposition(String input) {
        int count = 0;
        for (int x = 0; x < input.length(); x++) {
            if (variables.contains(input.charAt(x))) count++;
        }
        return count;
    }
    
    public static ArrayList<Boolean> solveTruthValues(String proposition) {
        if (propositions.containsKey(proposition)) {
            if (propositions.get(proposition) != null) return propositions.get(proposition);
        }
        proposition = proposition.replaceAll("\\s+","");
        ArrayList<Boolean> TruthValues = new ArrayList<>();
        ArrayList<Boolean> leftTruthValues = new ArrayList<>();
        ArrayList<Boolean> rightTruthValues = new ArrayList<>();
        String leftProposition = "";
        String rightProposition = "";
        String logicalConnective = "";
        if (proposition.equals(CompoundProposition)) {
            isCompoundPropositionNegated(proposition);
            leftProposition = CompoundPropositionLeft;
            rightProposition = CompoundPropositionRight;
            logicalConnective = CompoundPropositionLC;
        }
        
        if (proposition.startsWith("~") && proposition.length() == 2) {
            propositions.put(proposition, negation(propositions.get(proposition.substring(1))));
            return negation(propositions.get(proposition.substring(1)));
        }
        
        if (proposition.startsWith("(") && proposition.endsWith(")") && !proposition.equals(CompoundProposition)) {
            proposition = proposition.substring(1, proposition.length()-1);
        }
        
        if (proposition.startsWith("~(") && proposition.endsWith(")") && !proposition.substring(2).contains("(")) {
            ArrayList<Boolean> x = new ArrayList<>();
            x = propositions.get(proposition.substring(2, proposition.length()-1));
            propositions.put(proposition, negation(x));
            return negation(x);
        }
        
        if (proposition.startsWith("~(") && proposition.endsWith("))") && (!proposition.equals(CompoundProposition) || variables.size() == 1)) {
            ArrayList<Boolean> x = new ArrayList<>();
            if (propositions.get(proposition.substring(2, proposition.length())) != null) x = propositions.get(proposition.substring(2, proposition.length()-1));
            else x = solveTruthValues(proposition.substring(2, proposition.length()-1));
            propositions.put(proposition, negation(x));
            return negation(x);
        }
        
        if (proposition.startsWith("(") && !proposition.equals(CompoundProposition) && leftProposition.equals("") && rightProposition.equals("")) { 
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
        } else if (!proposition.startsWith("(") && !proposition.equals(CompoundProposition) && leftProposition.equals("") && rightProposition.equals("")) {
            leftProposition = getLeftRightProposition(proposition).get(0);
            rightProposition = getLeftRightProposition(proposition).get(1);
            logicalConnective = getLeftRightProposition(proposition).get(2);
        }
        
//        System.out.println("Proposition:"+proposition);
//        System.out.println("LEFT: "+leftProposition);
//        System.out.println("LC: "+logicalConnective);
//        System.out.println("RIGHT: "+rightProposition);
        
        if (rightProposition.contains("~") && rightProposition.length() == 2) {
            propositions.put(rightProposition, negation(propositions.get(rightProposition.substring(1, 2))));
        }
        
        if (leftProposition.contains("~") && leftProposition.length() == 2) {
            propositions.put(leftProposition, negation(propositions.get(leftProposition.substring(1, 2))));
        }
        
        if (propositions.get(leftProposition) != null && propositions.get(rightProposition) != null) {
            leftTruthValues = propositions.get(leftProposition);
            rightTruthValues = propositions.get(rightProposition);
        }
        
        if (propositions.get(leftProposition) == null) {
            leftTruthValues = solveTruthValues(leftProposition);
            rightTruthValues = propositions.get(rightProposition);
        }
        
        if (propositions.get(rightProposition) == null) {
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
    
    public static void displayTruthTable(int rows) {
        String[][] truthTable = new String[rows][50];
        int col = 1;
        int row = 0;
        String truthTableDisplay = "";
        while (row < rows) {
            truthTable[row][0] = "| ";
            col = 1;
            if (row == 0) {
                for (String proposition : propositions.keySet()) {
                    truthTable[row][col] = proposition + "  |  ";
                    col++;
                }
            } else {
                for (String proposition : propositions.keySet()) {
                    boolean truthValue = propositions.get(proposition).get(row-1);
                    int spacing = (int)Math.ceil(proposition.length()/2)+1;
                    int space = 0;
                    truthTable[row][col] = "";
                    while (space < spacing) {
                        if (col == 1) break;
                        truthTable[row][col] += "  ";
                        space++;
                    }
                    truthTable[row][col] += ((truthValue) ? 1 : 0);
                    space = 0 + ((proposition.length()%2==0) ? 1 : 0);
                    while (space < spacing) {
                        truthTable[row][col] += "  ";
                        space++;
                    }
                    truthTable[row][col] += "|";
                    col++;
                }
            }
            row++;
        }
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < 50; y++) {
                String truthTableRow = truthTable[x][y];
                if (truthTableRow != null) truthTableDisplay += truthTableRow; // System.out.print(truthTableRow);
            }
            truthTableDisplay += '\n';
        }
        JOptionPane.showMessageDialog(null, truthTableDisplay);
    }
    
    public static void main(String[] args) {
        String input = JOptionPane.showInputDialog("Enter Proposition: ");
        
        for (char x = 'a'; x <= 'z'; x++) {
            for (int y = 0; y < input.length(); y++) if (input.charAt(y) == x) variables.add(x);
        }
        
        int variableNumbers = variables.size();
        int numberOfRows = (int)Math.pow(2, variableNumbers);

        for (int vn = 0; vn < variableNumbers; vn++) {
            propositions.put(Character.toString(getVariableFromSet(vn)), initializeTruthTable(numberOfRows, variableNumbers, vn + 1));
        }
        
        for (char variable : variables) {
            ArrayList x = propositions.get(Character.toString(variable));
        }
        
        input = input.replaceAll("\\s+","");
        
        if (isValid(input)) {
            CompoundProposition = input;
            isCompoundPropositionNegated(CompoundProposition);
            getSimplePropositions(CompoundProposition);
            solveTruthValues(CompoundProposition);
            for (int x = 1; x <= NegateCompoundProposition; x++) {
                String p = "~(".repeat(x-1)+CompoundProposition+")".repeat(x-1);
                propositions.put("~(".repeat(x)+CompoundProposition+")".repeat(x), negation(propositions.get(p)));
            }
            removeDuplicates();
            displayTruthTable(numberOfRows+1);
//            System.out.println(input.replace("<->", "=").replace("->", "=>").replace("A", "and").replace("O", "xor"));
//            for (Character variable : variables) System.out.print(variable+",");
//            System.out.println();
        } else {
//            System.out.println("Invalid input!");
            JOptionPane.showMessageDialog(null, "Invalid input!");
        }
    }
}
