import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.List;

import language.Lexer;
import language.Parser;
import tokens.Token;


public class Main {
	
	public static void main(String[] args) throws FileNotFoundException {
		if(args.length < 1){
			System.out.println("Insufficient arguments");
			System.exit(1);
		}
		for(int i = 0; i < args.length; i++){
			Lexer lexer = new Lexer(new FileInputStream(new File(args[i])));
			List<Token> tokens = lexer.tokenize();
			
			for(Token t : tokens){
				System.out.println(t);
			}
			
			Parser parser = new Parser(tokens);
			parser.parse();
		}
		System.out.println("Done");
	}
	
}
