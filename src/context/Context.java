package context;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import statement.Statement;
import statement.Type;

public class Context {
	
	private HashMap<String, Type> variables;
	private List<Statement> statements;
	private Context parent;
	
	public Context(){
		this(null);
	}
	
	public Context(Context context){
		variables = new HashMap<String, Type>();
		statements = new ArrayList<Statement>();
	}
	
	public void addStatement(Statement statement){
		statements.add(statement);
	}
	
	public Type getTypeOfVariable(String name){
		return variables.get(name);
	}
	
	public void addVariable(String name, Type type){
		variables.put(name, type);
	}
	
	public Context getParent() {
		return parent;
	}
	
	public void setParent(Context parent) {
		this.parent = parent;
	}
}
