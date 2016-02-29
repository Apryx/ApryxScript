package statement;

import java.util.ArrayList;
import java.util.List;

import ast.ApryxClass;
import ast.Function;
import ast.Variable;

public class CodeBlock {
	
	private CodeBlock parent;
	
	private List<Function> functions;
	private List<Variable> variables;
	private List<ApryxClass> classes;
	
	private List<Statement> statements;
	
	public CodeBlock(){
		this(null);
	}
	
	public CodeBlock(CodeBlock parent){
		this.parent = parent;
		
		functions = new ArrayList<Function>();
		statements = new ArrayList<Statement>();
		variables = new ArrayList<Variable>();
		classes = new ArrayList<ApryxClass>();
	}

	public void add(Statement statement){
		this.statements.add(statement);
	}
	
	public void add(ApryxClass cls){
		this.classes.add(cls);
	}
	
	public void add(Function function){
		this.functions.add(function);
	}
	
	public void add(Variable variable){
		this.variables.add(variable);
	}
	
	public boolean isRoot(){
		return parent == null;
	}
	
	public CodeBlock getParent() {
		return parent;
	}
	
	public void setParent(CodeBlock parent) {
		this.parent = parent;
	}
	
	public Function getFunctionByName(String name, boolean local){
		for(Function f : functions){
			
			if(f.getName().equals(name))
				return f;
			
		}
		if(!local && parent != null)
			return parent.getFunctionByName(name, local);
		
		return null;
	}
	
	public Variable getVariableByName(String name, boolean local){
		for(Variable v : variables){
			if(v.getName().equals(name))
				return v;
			
		}
		if(!local && parent != null)
			return parent.getVariableByName(name, local);
		
		return null;
	}
	
	public ApryxClass getClassByName(String name, boolean local){
		for(ApryxClass c : classes){
			if(c.getName().equals(name))
				return c;
			
		}
		if(!local && parent != null)
			return parent.getClassByName(name, local);
		
		return null;
	}

	public List<Function> getFunctions() {
		return functions;
	}
	public List<Statement> getStatements() {
		return statements;
	}
	public List<Variable> getVariables() {
		return variables;
	}
	public List<ApryxClass> getClasses() {
		return classes;
	}
	
	@Override
	public String toString() {
		return statements.toString();
	}
	
	public void typeCheck() {
		//first check the variable types
		for(Variable v : variables){
			v.typeCheck(this);
		}
		//then functions and classes (Is this order dependent? I must look into this) TODO look into order
		for(Function f : functions){
			f.typeCheck();
		}
		for(ApryxClass c : classes){
			c.typeCheck();
		}
		
		for(Statement s : statements){
			s.typeCheck(this);
		}
	}
	
	public String toXML(){
		StringBuilder builder = new StringBuilder();
		
		for(ApryxClass c : classes){
			builder.append(c.toXML());
		}
		
		for(Variable v : variables){
			builder.append(v.toXML());
		}
		
		for(Function f : functions){
			builder.append(f.toXML());
		}
		
		for(Statement s : statements){
			builder.append(s.toXML());
		}
		
		return builder.toString();
	}
}
