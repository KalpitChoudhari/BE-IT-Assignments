package PackageWeather;


import java.io.IOException;

import org.apache.hadoop.conf.Configuration;

import org.apache.hadoop.fs.Path;

import org.apache.hadoop.io.IntWritable;

import org.apache.hadoop.io.LongWritable;

import org.apache.hadoop.io.Text;

import org.apache.hadoop.mapreduce.Job;

import org.apache.hadoop.mapreduce.Mapper;

import org.apache.hadoop.mapreduce.Reducer;

import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;

import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import org.apache.hadoop.util.GenericOptionsParser;

public class WeatherDemo {
	
	public static int max=99;
	public static int min=9999;
	public static int temp;
	public static int counter = 0;
	public static Text maxx = null;
	public static Text minn = null;
	public static String minnn = null;
	public static String maxxx = null;
public static void main(String [] args) throws Exception

{

Configuration c=new Configuration();

String[] files=new GenericOptionsParser(c,args).getRemainingArgs();

Path input=new Path(files[0]);

Path output=new Path(files[1]);

Job j=new Job(c,"wordcount");

j.setJarByClass(WeatherDemo.class);

j.setMapperClass(MapForWordCount.class);

j.setReducerClass(ReduceForWordCount.class);

j.setOutputKeyClass(Text.class);

j.setOutputValueClass(IntWritable.class);

FileInputFormat.addInputPath(j, input);

FileOutputFormat.setOutputPath(j, output);

System.exit(j.waitForCompletion(true)?0:1);

}

public static class MapForWordCount extends Mapper<LongWritable, Text, Text, IntWritable>{

public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException

{

	String line = value.toString();

	String temp = line.substring(87, 92); 
	String year = line.substring(15, 19);
	
	Text outputKey = new Text(year);
	
	IntWritable outputValue = new IntWritable(Integer.parseInt(temp));

	con.write(outputKey, outputValue);

}

}

public static class ReduceForWordCount extends Reducer<Text, IntWritable, Text, IntWritable>

{

public void reduce(Text word, Iterable<IntWritable> values, Context con) throws IOException, InterruptedException

{
	int sum = 0;
	int i=0;
	
	for(IntWritable value : values)
	{
		sum += value.get();
   		i++;
	}
	sum = sum / i;
	temp = sum;

	if(temp > max)
	{
		max = temp;
		maxxx = word.toString();
	}
	else if(temp < min)
	{
		min = temp;
		minn = word;
		minnn = word.toString();
	}
	//con.write(minn, new IntWritable(min));
	counter++;
	if(counter == 20)
	{
		con.write(new Text(minnn), new IntWritable(min));
		con.write(new Text(maxxx), new IntWritable(max));
	}
	
}
}
}
