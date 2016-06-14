package statement;

import context.Type;
import generation.JSGenerator;

public abstract class Expression implements JSGenerator{
	
	private Type type;
	
	public Expression(Type type){
		this.type = type;
	}
	
	public Type getType() {
		return type;
	}
	
	public void setType(Type type) {
		this.type = type;
	}
}
