import java.util.*;

public class mobilephone {
  float load = 0;
  char network;
  float ratePerText = 2f;
  float ratePerCall = 3.5f;
  
  mobilephone(char net){
    this.network = net;
  }
  
  
  public float checkBalance(){
    return load;
  } 
  
  public void call(float minutes, char network){
    float cost = minutes*ratePerCall;
    if(this.network != network){
      cost *= 2;
    }
    load = load - cost;
  }
  
  public void text(int length, char network){
    if(length>160){
      System.out.println("The limit is 160 texts.");
      return;
    }
    float cost = length*ratePerText;
    if(this.network != network){
      cost *= 2;
    }
    load = load - cost;
  }
  
  public void reload(float amount){
    load += amount;
  }
  
  
  public static void main(String[] args) {
    mobilephone realme = new mobilephone('G');
    realme.reload(250);
    realme.call(5, 'G');
    System.out.println(realme.checkBalance());
    
    realme.text(50, 'G');
    System.out.println(realme.checkBalance());
  }
}
