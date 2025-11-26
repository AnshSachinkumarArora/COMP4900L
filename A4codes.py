import torch
import torch.nn as nn
import torch.optim as optim
from torchvision import datasets, models, transforms
import os

def learn(in_domain): 
    device = torch.accelerator.current_accelerator().type if torch.accelerator.is_available() else "cpu"

    data_transforms = {
        'train': transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
    }

    in_dataset = datasets.ImageFolder(in_domain, data_transforms['train'])
    in_dataloader = torch.utils.data.DataLoader(in_dataset, batch_size=32, shuffle=True, num_workers=2)
    classes = in_dataset.classes
    model = models.resnet34(weights='IMAGENET1K_V1')
    model_ftrs = model.fc.in_features
    model.fc = nn.linear(model_ftrs, len(classes))
    model = model.to(device)
    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(model.parameters(), lr=0.001, momentum=0.9)
    num_epochs = 5
    model.train()
    
    #train
    for epochs in range(num_epochs):
        running_loss = 0.0
        for inputs, labels in in_dataloader:
            inputs = inputs.to(device)
            labels = labels.to(device)

            optimizer.zero_grad()

            output = model(inputs)
            loss = criterion(output, labels)

            loss.backward()
            optimizer.step()

            running_loss += loss.item()

    return model

def compute_accuracy(eval_folder, model):
    data_transforms = {
        'train': transforms.Compose([
            transforms.Resize(256),
            transforms.CenterCrop(224),
            transforms.ToTensor(),
            transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
        ])
    }

    in_dataset = datasets.ImageFolder(eval_folder, data_transforms['train'])
    in_dataloader = torch.utils.data.DataLoader(in_dataset, batch_size=32, shuffle=True, num_workers=2)

    model.eval()
    corrects = 0
    totals = 0
    with torch.no_grad():
        for inputs, labels in in_dataloader:
            inputs = inputs.to(device)
            labels = labels.to(device)

            outputs = model(inputs)
            _, preds = torch.max(outputs, 1)

            total += labels.size(0)
            correct += (preds == labels).sum().item()

    if total == 0:
        return 0.0
        
    return correct / total

in_domain_data = './A4Data/in-domain-train'

model = learn(in_domain_data)