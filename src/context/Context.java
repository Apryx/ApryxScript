package context;

import generation.JSGenerator;

import java.util.ArrayList;
import java.util.List;

import statement.Statement;

public class Context implements JSGenerator{
	
	protected List<ApryxVariable> variables;
	protected List<Statement> statements;
	protected List<Function> functions;
	protected List<ApryxClass> classes;
	protected Context parent;
	
	public Context(){
		this(null);
	}
	
	public Context(Context context){
		variables = new ArrayList<>();
		statements = new ArrayList<>();
		functions = new ArrayList<>();
		classes = new ArrayList<>();
	}
	
	public void addStatement(Statement statement){
		statements.add(statement);
	}
	
	public void addFunction(Function function){
		functions.add(function);
	}
	
	public void addVariable(ApryxVariable name){
		variables.add(name);
	}
	
	public void addClass(ApryxClass cls){
		classes.add(cls);
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
		
		for(int i = 0; i < classes.size(); i++){
			builder.append(classes.get(i).toJSString());
		}
		
		for(int i = 0; i < functions.size(); i++){
			builder.append(functions.get(i).toJSString());
		}
		
		for(int i = 0; i < variables.size(); i++){
			if(i == 0){
				builder.append("var ");
			}
			
			builder.append(variables.get(i).getName());
			if(variables.get(i).hasDefaultValue()){
				builder.append("=");
				builder.append(variables.get(i).getDefaultValue().toJSString());
			}
			
			if(i != variables.size() - 1){
				builder.append(", ");
			}else{
				builder.append(";");
			}
		}
		
		
		for(int i = 0; i < statements.size(); i++){
			builder.append(statements.get(i).toJSString());
		}
		
		return builder.toString();
	}
}
