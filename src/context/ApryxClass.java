package context;

public class ApryxClass extends Context{

	private String name;
	
	public ApryxClass(String name, Context parent){
		super(parent);
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public String toJSString() {
		
		StringBuilder builder = new StringBuilder();
		
		builder.append("function ");
		builder.append(name);
		builder.append("(){return new __");
		builder.append(name);
		builder.append("();}");
		
		String nName = "__" + name;
		
		builder.append("function ");
		builder.append(nName);
		builder.append("(){}");
		
		for(int i = 0; i < classes.size(); i++){
			builder.append(nName);
			builder.append(".prototype.");
			builder.append(classes.get(i).getName());
			builder.append("=");
			builder.append(classes.get(i).toJSString());
			builder.append(";");
		}
		

		for(int i = 0; i < functions.size(); i++){
			builder.append(nName);
			builder.append(".prototype.");
			builder.append(functions.get(i).getName());
			builder.append("=");
			builder.append(functions.get(i).toJSString());
			builder.append(";");
		}
		
		for(int i = 0; i < variables.size(); i++){
			builder.append(nName);
			builder.append(".prototype.");
			builder.append(variables.get(i).getName());
			if(variables.get(i).hasDefaultValue()){
				builder.append("=");
				builder.append(variables.get(i).getDefaultValue().toJSString());
			}
			builder.append(";");
		}
		
		
		//TODO not ignore statements now
		
		return builder.toString();
	}
	
}
