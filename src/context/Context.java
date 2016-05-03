package context;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import statement.Statement;
import statement.Type;

public class Context {
	
	private HashMap<String, Type> variables;
	private List<Statement> statements;
	
	public Context(){
		variables = new HashMap<String, Type>();
		statements = new ArrayList<Statement>();
	}
	
	public void addStatement(Statement statement){
		statements.add(statement);
	}
	
	public Type getTypeOfVariable(String name){
		return variables.get(name);
	}
}
