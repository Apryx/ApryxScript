package context;

import generation.JSGenerator;

import java.util.ArrayList;
import java.util.List;

import statement.Statement;

public class Context implements JSGenerator{
	
	private List<String> variables;
	private List<Statement> statements;
	private List<Function> functions;
	private Context parent;
	
	public Context(){
		this(null);
	}
	
	public Context(Context context){
		variables = new ArrayList<String>();
		statements = new ArrayList<Statement>();
		functions = new ArrayList<Function>();
	}
	
	public void addStatement(Statement statement){
		statements.add(statement);
	}
	
	public void addFunction(Function function){
		functions.add(function);
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
	
	@Override
	public String toJSString() {
		StringBuilder builder = new StringBuilder();
		
		for(int i = 0; i < variables.size(); i++){
			if(i == 0){
				builder.append("var ");
			}
			
			builder.append(variables.get(i));
			
			if(i != variables.size() - 1){
				builder.append(", ");
			}else{
				builder.append(";");
			}
		}
		

		for(int i = 0; i < functions.size(); i++){
			builder.append(functions.get(i).toJSString());
		}
		
		for(int i = 0; i < statements.size(); i++){
			builder.append(statements.get(i).toJSString());
		}
		
		return builder.toString();
	}
}
