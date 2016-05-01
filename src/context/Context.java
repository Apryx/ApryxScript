package context;

import java.util.HashMap;

import statement.Type;

public abstract class Context {
	
	private HashMap<String, Type> variables;
	
	public Context(){
		variables = new HashMap<String, Type>();
	}
	
	public Type getTypeOfName(String name){
		return variables.get(name);
	}
}
