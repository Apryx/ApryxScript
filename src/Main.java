import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.List;

import context.Context;
import language.Lexer;
import language.Parser;
import tokens.Token;


public class Main {
	
	private static boolean lexOnly = false;
	private static boolean typeCheck = true;
	private static String[] args;
	private static int filesOffset = 0;
	

	public static void parseArguments(){
		boolean arg = true;
		while(arg){
			if(args[filesOffset].equals("-l")){
				filesOffset++;
				lexOnly = true;
			}
			if(args[filesOffset].equals("-t")){
				filesOffset++;
				typeCheck = false;
			}
			else{
				arg = false;
			}
		}
	}
	
	public static void main(String[] args) throws FileNotFoundException {
		if(args.length < 1){
			System.out.println("Insufficient arguments");
			System.exit(1);
		}
		
		Main.args = args;
		parseArguments();
		
		for(int i = filesOffset; i < args.length; i++){
			File file = new File(args[i]);
			if(!file.exists()){
				System.err.println("Can't find file " + file.getAbsolutePath());
				break;
			}

			Lexer lexer = new Lexer(new FileInputStream(file));
			
			if(lexOnly){
				List<Token> tokens = lexer.tokenize();
				for(Token t : tokens){
					System.out.println(t);
				}
				return;
			}else{
				Parser parser = new Parser(lexer);
				Context context = parser.parseContext();
				if(typeCheck){
					context.checkType(null);
				}
				
				System.out.println(context.toJSString());
			}
			
			
		}
	}
	
	
	
}
