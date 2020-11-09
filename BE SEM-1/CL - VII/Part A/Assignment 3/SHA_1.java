/*
	Problem Statement :	Implement SHA-1 (Secure Hashing Algorithm)	
*/

import java.util.Scanner;
import java.math.BigInteger; 
import java.security.MessageDigest; 
import java.security.NoSuchAlgorithmException; 

public class SHA_1 { 
	public static String encryptThisString(String input) 
	{ 
		try {

			MessageDigest md = MessageDigest.getInstance("SHA-1"); 

			// digest() method is called to calculate message digest of the input string returned as array of byte 
			byte[] messageDigest = md.digest(input.getBytes()); 

			// Convert byte array into signum representation 
			BigInteger no = new BigInteger(1, messageDigest); 

			// Convert message digest into hex value 
			String hashtext = no.toString(16); 

			// Add preceding 0s to make it 32 bit 
			while (hashtext.length() < 32) { 
				hashtext = "0" + hashtext; 
			} 

			// return the HashText 
			return hashtext; 
		}
		catch (Exception e) { 
			throw new RuntimeException(e); 
		} 
	} 

	public static void main(String args[]) throws NoSuchAlgorithmException 
	{ 

		String s1, s2;

		Scanner sc = new Scanner(System.in); 
		
		System.out.print("Enter first String :");
		s1 = sc.nextLine();
		System.out.println(s1 + " : " + encryptThisString(s1)); 
		
		System.out.print("\nEnter second String :");
		s2 = sc.nextLine();
		System.out.println(s2 + " : " + encryptThisString(s2)); 
	} 
}