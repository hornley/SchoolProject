import java.io.*;
import java.util.*;

public class SymbolicLogicCalculator {
    public static LinkedHashMap<String, ArrayList<Boolean>> propositions = new LinkedHashMap<>();
    public static String[] logicalConnectives = {"A", "V", "O", "->", "<->", "==", "~"};
    public static Set<Character> variables = new HashSet<>();
    public static String CompoundProposition = "";
    public static String CompoundPropositionLeft = "";
    public static String CompoundPropositionRight = "";
    public static String CompoundPropositionLC = "";
    
    public static void getSimplePropositions(String input) {
        input = input.replaceAll("\\s+","");
        ArrayList<String> proposition = new ArrayList<>();
        int POcount = 0;
        HashMap<Integer, Integer> tempProposition = new HashMap<>();
        
        if (input.startsWith("(") && input.endsWith(")") && !input.equals(CompoundProposition)) {
            input = input.substring(1, input.length()-1);
        }
        if (input.length() == 2) return;
        
        for (int y = 0; y < input.length(); y++) {
            if (input.substring(y, y+1).equals("(")) {
                POcount++;
                if (input.substring(y-1, y).equals("~")) {
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
                    proposition.add(input.substring(y+1, y+4));
                }
            }
            for (String LC : logicalConnectives) {
                int from = y;
                if (POcount != 0 || LC.equals("~") || (!CompoundPropositionLeft.equals("") || !CompoundPropositionRight.equals("") || !CompoundPropositionLC.equals(""))) continue;
                else if (input.substring(y, y+1).equals(LC)) {
                    CompoundPropositionLeft = input.substring(0, y);
                    CompoundPropositionRight = input.substring(y+1, input.length());
                    CompoundPropositionLC = input.substring(y, y+1);
                }
                if (input.contains("->") || input.contains("<->")) {
                    if (input.substring(from, y+2).equals("->") || input.substring(from, y+2).equals("==")) {
                        CompoundPropositionLeft = input.substring(0, y);
                        CompoundPropositionRight = input.substring(y+2, input.length());
                        CompoundPropositionLC = input.substring(y, y+2);
                    } else if (input.substring(from, y+3).equals("<->")) {
                        CompoundPropositionLeft = input.substring(0, y);
                        CompoundPropositionRight = input.substring(y+3, input.length());
                        CompoundPropositionLC = input.substring(y, y+3);
                    }
                }
            }
        }
        
        for (String p : proposition) {
            
            if (p.startsWith("(") && p.endsWith(")") && !p.equals(CompoundProposition)) {
                p = p.substring(1, p.length()-1);
            }
            
            if (!propositions.keySet().contains(p)) {
                propositions.put(p, solveTruthValues(p));
            }
        }
    }
    
    public static String removeParenthesis(String input) {
        if (input.endsWith("))")) return input.substring(0, input.length()-1);
        if (input.contains("(") && input.contains(")") && input.startsWith("(")) return input.substring(1, input.length()-1);
        return input;
    }
    
    public static ArrayList<String> getLeftRightProposition(String input) {
        ArrayList<String> proposition = new ArrayList<>();
        
        for (int to = 0; to <input.length(); to++) {
            for (String LC : logicalConnectives) {
                if (LC.equals("~")) continue;
                if (input.substring(to, to+1).equals(LC)) {
                    proposition.add(input.substring(to-1, to));
                    proposition.add(removeParenthesis(input.substring(to+1, input.length())));
                    proposition.add(LC);
                    break;
                }
            }
            if (input.contains("->") || input.contains("<->")) {
                if (input.substring(to, to+2).equals("->")) {
                    proposition.add(input.substring(to-1, to));
                    proposition.add(removeParenthesis(input.substring(to+2, input.length())));
                    proposition.add("->");
                }
                if (input.substring(to, to+3).equals("<->")) {
                    proposition.add(input.substring(to-1, to));
                    proposition.add(removeParenthesis(input.substring(to+3, input.length())));
                    proposition.add("<->");
                }
            }
            if (!proposition.isEmpty()) break;
        }
//        System.out.println("Proposition: "+input);
//        System.out.println("PropositionsArray: "+proposition);
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
        if (proposition == CompoundProposition) {
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
        
        if (proposition.startsWith("~(") && proposition.endsWith("))") && !proposition.equals(CompoundProposition)) {
            ArrayList<Boolean> x = new ArrayList<>();
            if (propositions.get(proposition.substring(2, proposition.length())) != null) x = propositions.get(proposition.substring(2, proposition.length()-1));
            else x = solveTruthValues(proposition.substring(2, proposition.length()-1));
            propositions.put(proposition, negation(x));
            return negation(x);
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
        } else if (!proposition.startsWith("(") && !proposition.equals(CompoundProposition)) {
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
    
    public static void displayTruthTable(int rows) {
        String[][] truthTable = new String[rows][15];
        int col = 1;
        int row = 0;
        while (row < rows) {
            truthTable[row][0] = "| ";
            col = 1;
            if (row == 0) {
                for (String proposition : propositions.keySet()) {
                    truthTable[row][col] = proposition + " | ";
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
                        truthTable[row][col] += " ";
                        space++;
                    }
                    truthTable[row][col] += ((truthValue) ? 1 : 0);
                    space = 0 + ((proposition.length()%2==0) ? 1 : 0);
                    while (space < spacing) {
                        truthTable[row][col] += " ";
                        space++;
                    }
                    truthTable[row][col] += "|";
                    col++;
                }
            }
            row++;
        }
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < 15; y++) {
                String truthTableRow = truthTable[x][y];
                if (truthTableRow != null) System.out.print(truthTableRow);
            }
            System.out.println();
        }
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
        
        input = input.replaceAll("\\s+","");
        
        CompoundProposition = input;
        getSimplePropositions(input);
        solveTruthValues(input);
        displayTruthTable(numberOfRows+1);
    }
}