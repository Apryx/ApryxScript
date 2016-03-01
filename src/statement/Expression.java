package statement;

import ast.Type;

public abstract class Expression {
	
	protected Type type;
	
	public Expression(Type type){
		this.type = type;
	}
	
	public Type getType() {
		return type;
	}
	
	public abstract String toXML();
	public abstract void typeCheck(Context context);
	
}
