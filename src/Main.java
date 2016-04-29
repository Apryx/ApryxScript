import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.List;

import language.Lexer;
import language.ParserOld;
import language.TypeChecker;
import statement.CodeBlock;
import tokens.Token;


public class Main {
	
	private static boolean lexOnly = false;
	private static String[] args;
	private static int filesOffset = 0;
	

	public static void parseArguments(){
		boolean arg = true;
		while(arg){
			if(args[filesOffset].equals("-l")){
				filesOffset++;
				lexOnly = true;
			}else{
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
			
			List<Token> tokens = lexer.tokenize();
			
			if(lexOnly){
				for(Token t : tokens){
					System.out.println(t);
				}
				return;
			}
			
			
			
			ParserOld parser = new ParserOld(tokens);
			
			CodeBlock b = parser.parse();
			
			TypeChecker checker = new TypeChecker();
			checker.check(b);
			
			System.out.println("<program>"+parser.getBlock().toXML()+"</program>");
			
		}
	}
	
	
	
}
