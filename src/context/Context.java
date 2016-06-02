package context;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import statement.Statement;

public class Context {
	
	private Set<String> variables;
	private List<Statement> statements;
	private Context parent;
	
	public Context(){
		this(null);
	}
	
	public Context(Context context){
		variables = new HashSet<String>();
		statements = new ArrayList<Statement>();
	}
	
	public void addStatement(Statement statement){
		statements.add(statement);
	}
	
	public void addVariable(String name){
		variables.add(name);
	}
	
	public Context getParent() {
		return parent;
	}
	
	public void setParent(Context parent) {
		this.parent = parent;
	}
}
