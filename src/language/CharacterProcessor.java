package language;
import java.io.IOException;
import java.io.InputStream;

public class CharacterProcessor {
	
	private InputStream stream;
	private char current;
	private int line = 1;
	private boolean done = false;
	
	public CharacterProcessor(InputStream stream){
		this.stream = stream;
		next();
	}
	
	public char next(){
		//TODO look at this ugly function :)
		int read;
		try {
			if(current == '\n') // if previous was \n
				line++;
			
			read = stream.read();
			if(read <= 0){
				done = true;
			}
			current = (char) read;
			return current();
		} catch (IOException e) {
			e.printStackTrace();
		}
		done = true;
		return '\0';
	}
	
	public boolean isDone(){
		return done;
	}
	
	public char current(){
		return current;
	}
	
	public int getLine() {
		return line;
	}
}
